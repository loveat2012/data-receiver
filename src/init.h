#include "global.h"
#include "fcntl.h"
#include "dir.h"

static void usage(void);

void try_do_mkdir(const char *dir, const char *errmsg);

void init_global(char *conf_file);
