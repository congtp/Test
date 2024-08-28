#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

pid_t child_pid = 0;
volatile sig_atomic_t received_response = 0;

void handle_sigusr1(int sig) {
    // Child process will handle this signal to indicate it's alive
    if (child_pid == 0) {
        printf("Child: Received 'is_alive' signal from parent.\n");
        kill(getppid(), SIGUSR2);  // Send response back to parent
    }
}

void handle_sigusr2(int sig) {
    // Parent process will handle this signal to confirm child is alive
    printf("Parent: Received 'alive' response from child.\n");
    received_response = 1;  // Mark that we received a response
}

void handle_alarm(int sig) {
    // Parent process handles alarm if no response is received
    if (!received_response) {
        printf("Parent: No response from child, forking a new child process.\n");
        if (child_pid > 0) {
            kill(child_pid, SIGKILL);  // Kill the non-responsive child process
            wait(NULL);  // Wait for child process to terminate
        }
        child_pid = fork();
        if (child_pid == 0) {
            // Child process
            while (1) {
                pause();  // Wait for signals
            }
        }
        printf("Parent: New child process forked with PID %d.\n", child_pid);
    }
    received_response = 0;  // Reset the response flag
    alarm(1);  // Reset the alarm
}

int main() {
    signal(SIGUSR1, handle_sigusr1);  // Child process listens for SIGUSR1
    signal(SIGUSR2, handle_sigusr2);  // Parent process listens for SIGUSR2
    signal(SIGALRM, handle_alarm);    // Parent process handles alarm

    child_pid = fork();
    if (child_pid == 0) {
        // Child process
        while (1) {
            pause();  // Wait for signals
        }
    } else {
        // Parent process
        alarm(1);  // Set alarm for 1 second
        while (1) {
            if (child_pid > 0) {
                printf("Parent: Sending 'is_alive' signal to child.\n");
                kill(child_pid, SIGUSR1);  // Send "is_alive" signal to child
            }
            sleep(1);  // Wait for some time before next check
        }
    }

    return 0;
}
