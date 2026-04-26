#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>


int main() {
    pid_t pid1, pid2;

    // First child
    pid1 = fork();

    if (pid1 < 0) {
        printf("Fork failed!\n");
        return 1;
    }

    if (pid1 == 0) {
        // First child process
        printf("\n--- First Child ---\n");
        printf("PID: %d, PPID: %d\n", getpid(), getppid());
    } 
    else {
        // Only parent creates second child
        pid2 = fork();

        if (pid2 < 0) {
            printf("Fork failed!\n");
            return 1;
        }

        if (pid2 == 0) {
            // Second child process
            printf("\n--- Second Child ---\n");
            printf("PID: %d, PPID: %d\n", getpid(), getppid());
        } 
        else {
            // Parent process
            printf("\n--- Parent Process ---\n");
            printf("PID: %d\n", getpid());
            printf("First Child PID: %d\n", pid1);
            printf("Second Child PID: %d\n", pid2);
        }
    }

    return 0;
}