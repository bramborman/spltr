#include "info.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"


#define PFX_PART '-'
#define PFX_FILE ' '
#define SEP_FILE ':'
#define BYTES_FORMAT "%zu"


void winfo_part(FILE *const info, const char *const part_name) {
    size_t n = 0;
    n += fputc(PFX_PART, info);
    n += fputs(part_name, info);
    n += fputc('\n', info);

    if (n != 1 + strlen(part_name) + 1) {
        /* TODO: EXIT */
        return;
    }
}

void winfo_file(FILE *const info, const char *const file_name, const size_t file_bytes) {
    size_t n = 0;
    n += fputc(PFX_FILE, info);
    n += fputs(file_name, info);
    n += fputc(SEP_FILE, info);
    n += fprintf(info, BYTES_FORMAT, file_bytes);
    n += fputc('\n', info);

    if (n != 1 + strlen(file_name) + 1 + numlen(file_bytes) + 1) {
        /* TODO: EXIT */
        return;
    }
}

void rinfo(FILE *const info, const char *const *part_name, const char *const *file_name, size_t *file_bytes) {
    char prefix;
    size_t read = fread(&prefix, sizeof(char), 1, info);

    if (read != 1) {
        /* TODO: EXIT */
        return;
    }
    else {
        size_t eol_pos = eolpos(info);

        if (eol_pos == SIZE_INV) {
            /* TODO: EXIT */
            return;
        }
        else {
            long pos = ftell(info);

            if (pos == -1) {
                /* TODO: EXIT */
                return;
            }
            else {
                size_t line_len = eol_pos - (size_t)pos + 1;
                char *const line = malloc(line_len);

                if (line == NULL) {
                    /* TODO: EXIT */
                    return;
                }

                read = fread(line, sizeof(char), eol_pos, info);

                if (read != eol_pos) {
                    /* TODO: EXIT */
                    return;
                }

                if (prefix == PFX_PART) {
                    part_name = &line;
                    file_name = NULL;
                    file_bytes = NULL;

                    return;
                }
                else if (prefix == PFX_FILE) {
                    char *const sep = strrchr(line, SEP_FILE);

                    if (sep == NULL) {
                        /* TODO: EXIT */
                        return;
                    }
                    else {
                        int assigned = sscanf(sep + 1, BYTES_FORMAT, file_bytes);

                        if (assigned != 1) {
                            /* TODO: EXIT */
                            return;
                        }

                        part_name = NULL;
                        *sep = '\0';
                        file_name = &line;

                        return;
                    }
                }
                else {
                    /* TODO: EXIT */
                    return;
                }
            }
        }
    }
}
