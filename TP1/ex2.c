
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pid = fork();
    int s;
    if (pid < 0) {

    }
    if (pid == 0) {
        for (int i = 1; i < 50; i++) {
            printf("%d\n", i);
        }
        exit(0);
    }
    else {
        waitpid(pid, &s, 0);
        for (int i = 51; i <= 100; i++) {
            printf("%d\n", i);
        }
    }
    return 0;
}