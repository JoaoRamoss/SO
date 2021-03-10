#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main () {
    pid_t pid;
    int i = 0, status;

    if (pid = fork() == 0) {
        printf("Filho - pid: %d\n", getpid());
        printf("filho - pid pai: %d\n ", getppid());
        _exit(0);
    }
    else {
        pid_t terminated_pid = wait(&status);
        printf("\n terminated pid: %d --- %d\n",WEXITSTATUS(status), terminated_pid);
        printf("Pai - pid do filho: %d\n", pid);
        printf("Pai - pid: %d\n", getpid());
        printf("Pai - pid pai: %d\n", getppid());
    }
    return 0;
}