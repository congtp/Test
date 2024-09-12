#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <errno.h>
#include <sys/shm.h>     
#include <sys/ipc.h>

#define SERVER_PORT (9999)
#define BUFFER_SIZE (1024)
#define TIMEOUT_SEC (1)
#define SERVER_ADDR ("127.0.0.1")
#define IS_ALIVE    ("is_alive")
#define ALIVE       ("alive")
#define SHUTDOWN    ("shut down")
#define FORKED      (1)
#define NOT_FORKED  (0)
#define SHM_KEY     (1238)
#define MESSAGE_SIZE (1024)  
#define NUM_MESSAGES (5)     
#define SHM_SIZE (MESSAGE_SIZE * NUM_MESSAGES)       


#include "client.h"
#include "server.h"


#endif