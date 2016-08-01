#include <stdio.h>
#include <ntsid.h>
#include <time.h>
#include <string.h>


void get_time_string(char *time_string)
{
    time_t t = time(0);
    strftime(time_string, 20, "%F %T", localtime(&t));
}
