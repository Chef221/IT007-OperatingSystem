#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

pid_t child_pid = -1;
int ctrl_c_pressed = 0;

void handleCtrlC(int signal)
{
    if (signal == SIGINT)
    {
        if (ctrl_c_pressed == 0)
        {
            printf("\ncount.sh has stopped\n");
            if (child_pid > 0)
                kill(child_pid, SIGTERM);
            ctrl_c_pressed = 1;
        }
        else
        {
            printf("\nExiting program\n");
            exit(0);
        }
    }
}

int main(int argc, char *argv[])
{
    printf("Welcome to IT007, I am Nguyen Khoa Nguyen!\n");

    signal(SIGINT, handleCtrlC);

    child_pid = fork();
    if (child_pid == 0)
    {
        execl("./count.sh", "./count.sh", "120", NULL);
        perror("exec failed");
        exit(1);
    }
    else if (child_pid < 0)
    {
        perror("fork failed");
        exit(1);
    }

    int status;
    waitpid(child_pid, &status, 0);
    return 0;
}
