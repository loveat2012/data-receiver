#ifndef NULL
#define NULL 0
#endif
#define KEYLEN 100
#define MAX_PATHNAME_LENGTH 256

extern char queue_file[KEYLEN];
extern char listen_port[32];
extern char log_file[KEYLEN];
extern char error_log_file[KEYLEN];
extern int do_daemonize;
