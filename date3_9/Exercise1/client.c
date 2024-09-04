#include "client.h"


static void parent_init_handle(Parent_obj_t *pr_obj, Parent_State_t *state);
static void parent_send_is_alive_handle(Parent_obj_t *pr_obj, Parent_State_t *state);
static void parent_timeout_handle(Parent_obj_t *pr_obj, Parent_State_t *state);
static void parent_rx_alive_handle(Parent_obj_t *pr_obj, Parent_State_t *state);
static void parent_exit_handle(Parent_obj_t *pr_obj, Parent_State_t *state, int *pr_ex);

void process_entry(void){

    Parent_State_t pr_curr_state = PARENT_INIT;
    Parent_obj_t pr;
    int pr_exit = 1;
    int child_exit = 0;
    while(pr_exit){
        switch(pr_curr_state){
            case PARENT_INIT:
                parent_init_handle(&pr, &pr_curr_state);
                break;
            case PARENT_TIMEOUT:
                parent_timeout_handle(&pr, &pr_curr_state);
                break;
            case PARENT_RECEIVED_ALIVE:
                parent_rx_alive_handle(&pr, &pr_curr_state);
                break;
            case PARENT_SEND_IS_ALIVE:
                parent_send_is_alive_handle(&pr, &pr_curr_state);
                break;
            case PARENT_RETURN_TO_CHILD:
                child_exit = child_entry(&pr);
                break;
            case PARENT_EXIT:
                parent_exit_handle(&pr, &pr_curr_state, &pr_exit);
                break;
        }
        if(1 == child_exit && pr.pr_pid != getpid()){   // if pr_pid not equal to get pid ==> child
            break;
        }
    }
}

static void parent_init_handle(Parent_obj_t *pr_obj, Parent_State_t *state){
    // set obj to zero
    memset(pr_obj, 0, sizeof(*pr_obj));

    


    // config
    // pr_pid
    pr_obj->pr_pid = getpid();

    pr_obj->is_fork = 0;

    // pr_sock
    if ((pr_obj->pr_sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // pr_child_addr_struct
    struct sockaddr_in temp = {.sin_addr.s_addr = inet_addr(SERVER_ADDR), .sin_family = AF_INET, .sin_port = htons(SERVER_PORT)};
    memcpy(&pr_obj->chid_addr_structure, &temp, sizeof(struct sockaddr_in));

    // pr_addr_len
    pr_obj->chid_addr_len = sizeof(pr_obj->chid_addr_structure);

    // set sockopt
    pr_obj->pr_timeout.tv_sec = TIMEOUT_SEC;  // 2 seconds
    pr_obj->pr_timeout.tv_usec = 0; // 0 microseconds
    if (setsockopt(pr_obj->pr_sock, SOL_SOCKET, SO_RCVTIMEO, &(pr_obj->pr_timeout), sizeof(pr_obj->pr_timeout)) < 0) {
        perror("setsockopt failed");
        close(pr_obj->pr_sock);
        exit(EXIT_FAILURE);
    }

    // Create or access a shared memory segment
    pr_obj->pr_shm_id = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666);
    if (pr_obj->pr_shm_id < 0) {
        perror("shmget failed");
        fprintf(stderr, "Error code: %d\n", errno); // In ra mã lỗi errno 
        *state = PARENT_EXIT;
        return;
    }

    // Attach the shared memory segment to the process's address space
    pr_obj->pr_shm_ptr = (char *)shmat(pr_obj->pr_shm_id, NULL, 0);
    if (pr_obj->pr_shm_ptr == (char *)-1) {
        perror("shmat failed");
        *state = PARENT_EXIT;
        return;
    }

    *state = PARENT_SEND_IS_ALIVE;
} 

static void parent_send_is_alive_handle(Parent_obj_t *pr_obj, Parent_State_t *state){
    //IS_ALIVE
    memset(pr_obj->pr_tx_buffer, 0, BUFFER_SIZE);
    strcpy(pr_obj->pr_tx_buffer, IS_ALIVE);

    // sendto 
    sendto(pr_obj->pr_sock, pr_obj->pr_tx_buffer, strlen(pr_obj->pr_tx_buffer), 0, (const struct sockaddr *)&(pr_obj->chid_addr_structure), pr_obj->chid_addr_len);

    // revcfrom
    pr_obj->pr_rx_len = recvfrom(pr_obj->pr_sock, pr_obj->pr_rx_buffer, sizeof(pr_obj->pr_rx_buffer), 0, (struct sockaddr *)&(pr_obj->chid_addr_structure), &(pr_obj->chid_addr_len));

    if ((0 > pr_obj->pr_rx_len) && (NOT_FORKED == pr_obj->is_fork)) {
        perror("recvfrom failed or timed out not forked");
        *state = PARENT_TIMEOUT;
    }else if((0 > pr_obj->pr_rx_len) && (FORKED == pr_obj->is_fork)){
        perror("recvfrom failed or timed out forked");
    }else {
        pr_obj->pr_rx_buffer[pr_obj->pr_rx_len] = '\0'; // Null-terminate the string
        printf("Parent: Received message: %s\n", pr_obj->pr_rx_buffer);
        printf("\n");
        *state = PARENT_RECEIVED_ALIVE;
    }
}


static void parent_timeout_handle(Parent_obj_t *pr_obj, Parent_State_t *state){
    // Fork a new process if no response
    pid_t temp = fork();

    if (0 == temp) {
        // Child process acts as the server
        printf("Child process created\n");
        *state = PARENT_RETURN_TO_CHILD; 
    } else if (0 < temp) {
        // Parent process continues
        printf("Parent: Forked a child process with PID %d\n", temp);
        pr_obj->is_fork = FORKED;
        *state = PARENT_SEND_IS_ALIVE;
    } else {
        // Fork failed
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
}

static void parent_rx_alive_handle(Parent_obj_t *pr_obj, Parent_State_t *state){

    // write msg to shared memory
    for (int i = 0; i < NUM_MESSAGES; i++) {
        char message[1024];
        snprintf(message, sizeof(message), "Message %d from parent process", i + 1);

        // calculate offset
        int offset = i * MESSAGE_SIZE;

        // write msg to shared memory
        memset(pr_obj->pr_shm_ptr + offset, 0, MESSAGE_SIZE);
        strncpy(pr_obj->pr_shm_ptr + offset, message, MESSAGE_SIZE);
        printf("Parent: Written to shared memory: %s\n", pr_obj->pr_shm_ptr + offset);

        sleep(1);  // Simulate some delay
    }


    // Detach from shared memory
    if (shmdt(pr_obj->pr_shm_ptr) < 0) {
        perror("shmdt failed");
        *state = PARENT_EXIT;
        return;
    }

    *state = PARENT_EXIT;
}

static void parent_exit_handle(Parent_obj_t *pr_obj, Parent_State_t *state, int *pr_ex){

    // send shutdown 
    //IS_ALIVE
    memset(pr_obj->pr_tx_buffer, 0, BUFFER_SIZE);
    strcpy(pr_obj->pr_tx_buffer, SHUTDOWN);

    // sendto 
    sendto(pr_obj->pr_sock, pr_obj->pr_tx_buffer, strlen(pr_obj->pr_tx_buffer), 0, (const struct sockaddr *)&(pr_obj->chid_addr_structure), pr_obj->chid_addr_len);


    int status;
    printf("Enter Parent Exit\n");
    wait(&status); // Wait for any child process to finish
    if (WIFEXITED(status)) {
        printf("Parent: Child process terminated with status %d\n", WEXITSTATUS(status));
    }
    *pr_ex = 0;
    if (shmctl(pr_obj->pr_shm_id, IPC_RMID, NULL) < 0) {
        perror("shmctl failed");
        exit(EXIT_FAILURE);
    }
    close(pr_obj->pr_sock);
}

