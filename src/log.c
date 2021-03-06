#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "global.h"
#include "timer.h"
#include "fcntl.h"


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
            lfmsg[lfmsg_len - 2] = '\n';
            write_file_with_lock(fp, lfmsg, lfmsg_len - 1);
            free(lfmsg);
            fclose(fp);
        } else {
            fclose(fp);
            perror("Can't allocate LF msg memory");
        }
    } else {
        perror("Can't open file");
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
