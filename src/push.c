#include "string.c"
#include "global.h"
#include "parse_conf.c"
#include "fcntl.c"
#include "dir.c"
#include "time.c"
#include "log.c"
#include "protocol.c"

int main(int argc, char *argv[])
{
    int ch;
    int set_file_opt = 0;
    char *conf_file;

    while ((ch = getopt(argc, argv, "f:d")) != -1) {
        switch (ch) {
            case 'f':
                set_file_opt = 1;
                conf_file = optarg;
                if (is_file_exist(conf_file) != 0) {
                    perror("Configure file dose not exists");
                    return -1;
                }
                break;
            case 'd':
                do_daemonize = 1;
                break;
        }
    }

    if (set_file_opt == 0) {
        usage();
        return -1;
    }

    init_global(conf_file);
    communication(receive_callback);
    return 0;
}

static void usage(void)
{
    printf(PACKAGE
    " : "
    VERSION
    "\n");
    printf("Usage: push -f configure-file \n");
    printf("argments: \n");
    printf("-f      the path of configure file)\n");
    return;
}

void try_do_mkdir(const char *dir, const char *errmsg)
{
    if (is_dir_exist(dir)) {
        if (mkdirs(dir) == -1) {
            perror(errmsg);
            exit(-1);
        }
    }
}

void init_global(char *conf_file)
{
    get_profile_conf(conf_file, "file_queue", "queue_file", queue_file);
    if (is_file_exist(queue_file) != 0) {
        char *queue_dir = dirname(queue_file);
        try_do_mkdir(queue_dir, "Can't create queue directory");
    }
    get_profile_conf(conf_file, "file_queue", "listen_port", listen_port);
    get_profile_conf(conf_file, "file_queue", "log_file", log_file);
    if (is_file_exist(log_file) != 0) {
        char *log_dir = dirname(log_file);
        try_do_mkdir(log_dir, "Can't create log directory");
    }
    get_profile_conf(conf_file, "file_queue", "error_log_file", error_log_file);
    if (is_file_exist(error_log_file) != 0) {
        char *error_log_dir = dirname(error_log_file);
        try_do_mkdir(error_log_dir, "Can't create error log directory");
    }
}
