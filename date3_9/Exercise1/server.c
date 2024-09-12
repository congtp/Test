#include "server.h"


static void child_init_handle(Parent_obj_t *pr_obj, Child_obj_t *child_obj, Child_State_t *state);
static void child_check_msg_handle(Child_obj_t *child_obj, Child_State_t *state);
static void child_check_is_alive_handle(Child_obj_t *child_obj, Child_State_t *state);

int child_entry(Parent_obj_t *pr_obj){
    Child_State_t child_curr_state = CHILD_INIT;
    Child_obj_t child;
    int is_exit = 1;
    while(is_exit){
        switch(child_curr_state){
            case CHILD_INIT:
                child_init_handle(pr_obj, &child, &child_curr_state);
                break;
            case CHILD_CHECK_IS_ALIVE:
                child_check_is_alive_handle(&child, &child_curr_state);
                break;
            case CHILD_CHECK_MSG:
                child_check_msg_handle(&child, &child_curr_state);
                break;
            case CHILD_SEND_IS_ALIVE:
                
                break;
            case CHILD_HANDLE_MSG:
                child_curr_state = CHILD_CHECK_IS_ALIVE;
                break;
            case CHILD_EXIT:
                close(child.child_sock);
                is_exit = 0;
                break;
        }
    }
    return 1;
}


static void child_init_handle(Parent_obj_t *pr_obj, Child_obj_t *child_obj, Child_State_t *state){

    // set obj to zero
    memset(child_obj, 0, sizeof(*child_obj));

    child_obj->child_pid = getpid();
    // Create a new UDP socket
    if ((child_obj->child_sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Child: Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memcpy(&(child_obj->child_addr_structure), &(pr_obj->chid_addr_structure), sizeof(pr_obj->chid_addr_structure));
    child_obj->child_addr_len = sizeof(child_obj->child_addr_structure);
    
    child_obj->child_shm_id = pr_obj->pr_shm_id;
    child_obj->child_shm_ptr = pr_obj->pr_shm_ptr;



    // Bind the socket to the server address
    if (bind(child_obj->child_sock, (const struct sockaddr *)&(child_obj->child_addr_structure), child_obj->child_addr_len) < 0) {
        perror("Child: Socket bind failed");
        close(child_obj->child_sock); // Close the socket before exiting
        exit(EXIT_FAILURE);
    }
    *state = CHILD_CHECK_IS_ALIVE;
}

static void child_check_is_alive_handle(Child_obj_t *child_obj, Child_State_t *state){
    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);
    memset(child_obj->child_rx_buffer, 0, BUFFER_SIZE);
    child_obj->child_rx_len = recvfrom(child_obj->child_sock, child_obj->child_rx_buffer, BUFFER_SIZE, MSG_DONTWAIT, (struct sockaddr *)&client_addr, &len);
    if (child_obj->child_rx_len < 0) {
        if (errno != EAGAIN && errno != EWOULDBLOCK) {
            perror("Child: recvfrom() failed");
        }else{
            //printf("CHILD ENTER ELSE\n");
            *state = CHILD_CHECK_MSG;
        }
    } else if (child_obj->child_rx_len > 0) {
        child_obj->child_rx_buffer[child_obj->child_rx_len] = '\0'; // Null-terminate the received string
        if (strcmp(child_obj->child_rx_buffer, IS_ALIVE) == 0) {
            //printf("Child: Responding to 'is_alive' message.\n");
            memset(child_obj->child_tx_buffer, 0, BUFFER_SIZE);
            strcpy(child_obj->child_tx_buffer, ALIVE);
            printf("child msg: %s\n", child_obj->child_tx_buffer);
            if (sendto(child_obj->child_sock, child_obj->child_tx_buffer, strlen(child_obj->child_tx_buffer), 0, (struct sockaddr *)&client_addr, len) < 0) {
                perror("Child: Failed to send 'alive' response");
            }
            *state = CHILD_CHECK_MSG;
        }else if(strcmp(child_obj->child_rx_buffer, SHUTDOWN) == 0){

            printf("Child: Received 'SHUTDOWN' message, exiting.\n");
            *state = CHILD_EXIT;
        }
        
        //break; // Exit the loop after handling the message
    }
    

}


static void child_check_msg_handle(Child_obj_t *child_obj, Child_State_t *state){
    
    if (child_obj->child_shm_ptr[0] != '\0') {

        strncpy(child_obj->child_rx_buffer, child_obj->child_shm_ptr, BUFFER_SIZE);
        printf("Child: Received message from shared memory: %s\n", child_obj->child_shm_ptr);

        child_obj->child_shm_ptr = &(child_obj->child_shm_ptr[BUFFER_SIZE]);

        *state = CHILD_HANDLE_MSG;
    } else {

        *state = CHILD_CHECK_IS_ALIVE;
    }
}
