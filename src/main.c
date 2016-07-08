#include <getopt.h>
#include <stdio.h>
#include "init.h"
#include "protocol.h"
#include "setup.h"


int do_daemonize = 0;

int is_file_exist(const char *file);

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
    printf(PACKAGE " : " VERSION "\n");
    printf("Usage: " PACKAGE " -f configure-file \n");
    printf("argments: \n");
    printf("-f      the path of configure file\n");
    return;
}
