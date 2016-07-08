#include "fcntl.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/fcntl.h>


int is_file_exist(const char *file)
{
    if (file == NULL) {
        return -1;
    }
    return (access(file, F_OK) ? (-1) : 0);
}

void write_file_with_lock(FILE *fp, const void *ptr, size_t size)
{
    flock((int) fp, LOCK_EX);
    fwrite(ptr, size, 1, fp);
    flock((int) fp, LOCK_UN);
    fclose(fp);
}
