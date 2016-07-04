#define MAX_PATHNAME_LENGTH 256

int is_file_exist(const char *file);

void write_file_with_lock(FILE *fp, const void *ptr, size_t size);
