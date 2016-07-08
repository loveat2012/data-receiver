#include "global.h"
#include "time.h"
#include "fcntl.h"
#include "log.h"


char log_file[KEYLEN];
char error_log_file[KEYLEN];

void write_log(const char *filename, const char *msg)
{
    FILE *fp;
    fp = fopen(filename, "a+");
    if (fp != NULL) {
        int lfmsg_len = strlen(msg) + 24;
        char *lfmsg = (char *) malloc(lfmsg_len);
        if (lfmsg != NULL) {
            memset(lfmsg, 0, sizeof(*lfmsg));
            char time_string[23];
            get_time_string(time_string);
            strcat(time_string, " : ");
            strcat(lfmsg, time_string);
            strcat(lfmsg, msg);
            lfmsg[lfmsg_len - 1] = '\n';
            write_file_with_lock(fp, lfmsg, lfmsg_len);
            free(lfmsg);
        }
        fclose(fp);
    }
}

void log_info(const char *info)
{
    write_log(log_file, info);
}

void log_error(const char *errmsg)
{
    write_log(error_log_file, errmsg);
}
