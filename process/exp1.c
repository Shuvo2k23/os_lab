#include <sys/types.h>
#include <unistd.h>
#include<stdio.h>

int main() {
    pid_t pid;

    pid = fork();   // create child process

    if (pid < 0) {
        // Fork failed
        printf("Fork failed!\n");
    }
    else if (pid == 0) {
        // Child process
        printf("\n--- Child Process ---\n");
        printf("Child PID: %d\n", getpid());
        printf("Parent PID (PPID of child): %d\n", getppid());
    }
    else {
        // Parent process
        printf("\n--- Parent Process ---\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID (returned to parent): %d\n", pid);
    }

    return 0;
}