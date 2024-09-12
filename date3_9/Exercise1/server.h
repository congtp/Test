#ifndef __SERVER_H__
#define __SERVER_H__

#include "main.h"

typedef struct Parent_obj_t Parent_obj_t;

typedef enum {
    CHILD_INIT,
    CHILD_CHECK_IS_ALIVE,
    CHILD_CHECK_MSG,
    CHILD_SEND_IS_ALIVE,
    CHILD_HANDLE_MSG,
    CHILD_EXIT
} Child_State_t;

typedef struct{
    pid_t child_pid;
    struct sockaddr_in pr_addr_structure;
    socklen_t pr_addr_len;
    struct sockaddr_in child_addr_structure;
    socklen_t child_addr_len;
    int child_sock;
    struct timeval child_timeout;
    int child_shm_id;
    char *child_shm_ptr;
    int child_rx_len;
    char child_rx_buffer[BUFFER_SIZE];
    char child_tx_buffer[BUFFER_SIZE];
}Child_obj_t;


int child_entry(Parent_obj_t *pr_obj);



#endif