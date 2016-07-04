#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <libgen.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/file.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <memory.h>
#include <time.h>
#include <errno.h>

#define PACKAGE "data-receiver"
#define VERSION "0.0.1"
#define KEYLEN 100
#define LINESIZE 1024
#define MAX_PATHNAME_LENGTH 256

char queue_file[KEYLEN];
char listen_port[32];
char log_file[KEYLEN];
char error_log_file[KEYLEN];
int do_daemonize = 0;

static void usage(void);
void try_do_mkdir(const char *dir, const char *errmsg);
void init_global(char *conf_file);