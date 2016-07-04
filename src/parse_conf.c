#include "parse_conf.h"

int get_profile_conf(const char *conf_file, const char *profile, const char *key, char *value)
{
    FILE *fp;
    char conf_profile[32];
    char conf_key[KEYLEN];
    char src_line[LINESIZE];
    char *dst_line, *c;
    int found = 0;

    if ((fp = fopen(conf_file, "r")) == NULL) {
        perror("Can't open config file");
    }

    memset(conf_profile, 0, sizeof(conf_profile));
    sprintf(conf_profile, "[%s]", profile);

    while (!feof(fp) && fgets(src_line, LINESIZE, fp)) {
        dst_line = ltrim(src_line);

        if (strlen(dst_line) <= 0) {
            continue;
        }

        if (found == 0) {
            if (dst_line[0] != '[') {
                continue;
            } else if (strncmp(dst_line, conf_profile, strlen(conf_profile)) == 0) {
                found = 1;
                continue;
            }
        } else {
            if (dst_line[0] == '#') {
                continue;
            } else if (dst_line[0] == '[') {
                break;
            } else {
                if ((c = strchr(dst_line, '=')) == NULL) {
                    continue;
                }
                memset(conf_key, 0, sizeof(conf_key));
                sscanf(dst_line, "%[^=|^ |^\t]", conf_key);
                if (strcmp(key, conf_key) == 0) {
                    sscanf(++c, "%[^\n]", value);
                    char *dst_value = (char *) malloc(strlen(value) + 1);
                    if (dst_value == NULL) {
                        perror("Can't allocate dst_value");
                        exit(-1);
                    }
                    memset(dst_value, 0, sizeof(*dst_value));
                    strcpy(dst_value, value);
                    strcpy(value, trim(dst_value));
                    free(dst_value);
                    found = 2;
                    break;
                }
            }
        }
    }
    fclose(fp);
    return found == 2 ? 0 : -1;
}
