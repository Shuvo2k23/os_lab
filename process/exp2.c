#include <sys/types.h>
#include <unistd.h>
#include<stdio.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork failed!\n");
        return 1;
    }
    else if (pid == 0) {
        // Child process
        printf("\n--- Child Process ---\n");
        for (int i = 6; i <= 10; i++) {
            printf("%d ", i);
        }
        printf("\n");
    }
    else {
        // Parent process
        printf("\n--- Parent Process ---\n");
        for (int i = 1; i <= 5; i++) {
            printf("%d ", i);
        }
        printf("\n");
    }

    return 0;
}