#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include "fcntl.h"


int is_dir_exist(const char *path)
{
    return is_file_exist(path);
}

int mkdirs(const char *path)
{
    int ret;
    int len;
    char subpath[MAX_PATHNAME_LENGTH] = "";
    char *pos = NULL;
    char pth[MAX_PATHNAME_LENGTH];

    if (path == NULL) {
        return -1;
    }
    strcpy(pth, path);
    if ((len = strlen(pth)) > 0 && pth[len - 1] == '/') {
        pth[len - 1] = '\0';
    }

    while ((ret = mkdir(pth, S_IRWXU)) != 0) {
        if (errno == EEXIST) {
            return 0;
        } else if (errno == EACCES || errno == EROFS) {
            return ret;
        }

        if ((pos = strrchr(pth, '/')) == NULL) {
            return ret;
        }

        strncat(subpath, pth, pos - pth);
        mkdirs(subpath);
    }
    return ret;
}
