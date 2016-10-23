

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>

#include "debug.h"
#include "memory.h"

int main(int argc, char *argv[]){
	/* Disable warnings */
	(void)argc; (void)argv;
    size_t size = 1024;
    char *cmd = MALLOC(size);
    do {
        printf("Your request? ");
        fflush(stdout);
        ssize_t n = getline(&cmd, &size, stdin);
        if (n <= 0) {
            break;
        }
        cmd[n-1] = 0;
        if (strcasecmp(cmd, "quit") == 0) {
            break;
        }
        pid_t pid = fork();
        if (pid == 0) {
            execlp(cmd, cmd, NULL);
            ERROR(1, "execl() failed");
        }
        int exit_code;
        wait(&exit_code);
        printf("\nProcesso terminou com exit: %d\n", exit_code);
    } while (1);
    free(cmd);
	return 0;
}

