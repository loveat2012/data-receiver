#include "daemonize.h"

int daemonize(void)
{
    pid_t pid;
    int fd;
    int i;

    if ((pid = fork()))
        exit(0);
    else if (pid < 0)
        exit(1);

    setsid();
    if ((pid = fork()))
        exit(0);
    else if (pid < 0)
        exit(1);

    if ((fd = open("/dev/null", O_RDWR, 0)) != -1) {
        if(dup2(fd, STDIN_FILENO) < 0) {
            perror("dup2 stdin");
            return (-1);
        }
        if(dup2(fd, STDOUT_FILENO) < 0) {
            perror("dup2 stdout");
            return (-1);
        }
        if(dup2(fd, STDERR_FILENO) < 0) {
            perror("dup2 stderr");
            return (-1);
        }

        if (fd > STDERR_FILENO) {
            if(close(fd) < 0) {
                perror("close");
                return (-1);
            }
        }
    }

    /*signal(SIGTTOU, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGHUP, SIG_IGN);*/

    chdir("/tmp");
    umask(0);

    return 0;
}