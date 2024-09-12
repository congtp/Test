#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "main.h"

typedef enum {
    PARENT_INIT,
    PARENT_TIMEOUT,
    PARENT_RECEIVED_ALIVE,
    PARENT_SEND_IS_ALIVE,
    PARENT_SEND_PACKAGE,
    PARENT_RETURN_TO_CHILD,
    PARENT_EXIT
} Parent_State_t;

typedef struct Parent_obj_t{
    pid_t pr_pid;
    int is_fork;
    struct sockaddr_in chid_addr_structure;
    socklen_t chid_addr_len;
    int pr_sock;
    struct timeval pr_timeout;
    int pr_shm_id;
    char *pr_shm_ptr;
    int pr_rx_len;
    char pr_rx_buffer[BUFFER_SIZE];
    char pr_tx_buffer[BUFFER_SIZE];
}Parent_obj_t;


void process_entry(void);

#endif