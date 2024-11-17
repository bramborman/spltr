#include "merge.h"

#include <stdarg.h>
#include "info.h"
#include "program.h"
#include "utils.h"


static void _free(void) {
}

static void _exit_fail(_Printf_format_string_ const char *const message_format, ...) {
    _free();

    {
        va_list args;
        va_start(args, message_format);
        vexit_fail(FALSE, message_format, args);
        va_end(args);
    }
}

BOOL merge(const CONFIG *const config) {
    const char *const info_name = *config->paths;

    FILE *const info = fopen(info_name, "rbS");

    if (info == NULL) {
        /* TODO: Exit */
        return FALSE;
    }
    else {
        FILE *part = NULL;
        FILE *file = NULL;
        void *buff = NULL;
        size_t buff_len = 0;

        while (!feof(info)) {
            const char *const part_name = NULL;
            const char *const file_name = NULL;
            size_t file_bytes;
            rinfo(info, &part_name, &file_name, &file_bytes);

            if (part_name != NULL) {
                // Don't close previous - have them all locked until we quit
                part = fopen(part_name, "TODO");  /* TODO */

                if (part == NULL) {
                    /* TODO: Exit */
                    return FALSE;
                }
            }
            else if (file_name != NULL) {
                if (part == NULL) {
                    /* TODO: Exit */
                    return FALSE;
                }

                // Don't close previous - have them all locked until we quit
                file = fopen(file_name, "TODO");  /* TODO */

                if (file == NULL) {
                    /* TODO: Exit */
                    return FALSE;
                }

                if (file_bytes <= 0) {
                    continue;
                }
                else {
                    const size_t clamped_file_bytes = min(file_bytes, MAX_MEM);

                    if (buff_len < clamped_file_bytes) {
                        buff_len = clamped_file_bytes;

                        {
                            void *const new_buff = srealloc(buff, &buff_len);

                            if (new_buff == NULL) {
                                /* TODO: EXIT */
                                return FALSE;
                            }

                            buff = new_buff;
                        }
                    }

                    while (file_bytes > 0) {
                        size_t processed = fread(buff, 1, buff_len, part);

                        if (processed != buff_len) {
                            /* TODO: EXIT */
                            return FALSE;
                        }

                        processed = fwrite(buff, 1, buff_len, file);

                        if (processed != buff_len) {
                            /* TODO: EXIT */
                            return FALSE;
                        }

                        file_bytes -= buff_len;
                    }
                }
            }
            else {
                /* TODO: Exit */
                return FALSE;
            }
        }
    }

    _free();
    return TRUE;
}