#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include "init.h"


char queue_file[KEYLEN];
char listen_port[32];
char log_file[KEYLEN];
char error_log_file[KEYLEN];

int get_profile_conf(const char *conf_file, const char *profile, const char *key, char *value);

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
