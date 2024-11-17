#include "split.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "info.h"
#include "program.h"
#include "res.h"
#include "utils.h"


static struct _RC {
    const CONFIG *config;
    size_t part_num;
    const char *part_name;
    void *buff;
} _rc;


static void _free(void) {
    free((void *)_rc.part_name);
    free(_rc.buff);
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

#define GET_NAME_TEMPLATE(NAME, FORMAT_AD, EXT, ARG, LEN_AD, CODE_BFR)                          \
    static const char *NAME(void) {                                                             \
        CODE_BFR;                                                                               \
                                                                                                \
        {                                                                                       \
            const int len = (int)_rc.config->name_len + LEN_AD;                                 \
            char *const part_name = malloc(len);                                                \
                                                                                                \
            if (part_name == NULL) {                                                            \
                _exit_fail(RES_ERR_CANNOT_ALLOCATE);                                            \
                return NULL;                                                                    \
            }                                                                                   \
            else {                                                                              \
                const int num = sprintf(part_name, "%s"FORMAT_AD##EXT, _rc.config->name, ARG);  \
                                                                                                \
                if (num != len) {                                                               \
                    _exit_fail(RES_ERR_UNKNOWN);                                                \
                    return NULL;                                                                \
                }                                                                               \
                                                                                                \
                return part_name;                                                               \
            }                                                                                   \
        }                                                                                       \
    }

GET_NAME_TEMPLATE(
    _get_info_name,
    "_info%s",
    EXT_INFO,
    "",
    1 + 4 + EXT_INFO_LEN,
    ;);
#define PART_NUM_LEN        3
#define PART_NUM_LEN_STR    "3"
GET_NAME_TEMPLATE(
    _get_next_out_name,
    "_"RES_PART"%0"PART_NUM_LEN_STR"zu",
    EXT_PART,
    ++_rc.part_num,
    1 + RES_PART_LEN + max(PART_NUM_LEN, nl) + EXT_PART_LEN,
    const int nl = (int)numlen(_rc.part_num));
#undef PART_NUM_LEN
#undef GET_NAME_TEMPLATE

BOOL split(const CONFIG *const _config) {
    _rc.config = _config;
    _rc.part_num = 0;
    _rc.part_name = NULL;
    /* TODO: Use srealloc */
    _rc.buff = malloc(_rc.config->split_size);

    if (_rc.buff == NULL) {
        _exit_fail(RES_ERR_CANNOT_ALLOCATE);
        return FALSE;
    }
    else {
        const char *const info_name = _get_info_name();
        FILE *const info = fopen(info_name, "wxbS");

        if (info == NULL) {
            _exit_fail(RES_ERR_CANNOT_CREATE_FILE_1, info_name);
            return FALSE;
        }
        else {
            /* TODO: Cannot free sprintf'ed string?? free((void *)info_name); */

            {
                size_t remaining_bytes = 0UL;
                FILE *file = NULL;
                FILE *part = NULL;
                int paths_i;

                for (paths_i = 0; paths_i < _rc.config->path_count; paths_i++) {
                    const char *const path = _rc.config->paths[paths_i];

                    // Don't close previous - have them all locked until we quit
                    file = fopen(path, "rb");

                    if (file == NULL) {
                        _exit_fail(RES_ERR_CANNOT_OPEN_FILE_1, path);
                        return FALSE;
                    }

                    do {
                        if (remaining_bytes == 0UL || part == NULL) {
                            /* TODO: Cannot free sprintf'ed string?? free((void *)_rc.out_name); */

                            if (part != NULL) {
                                fclose(part);
                            }

                            _rc.part_name = _get_next_out_name();
                            part = fopen(_rc.part_name, "wxbS");

                            if (part == NULL) {
                                _exit_fail(RES_ERR_CANNOT_CREATE_FILE_1, _rc.part_name);
                                return FALSE;
                            }

                            remaining_bytes = _rc.config->split_size;
                            winfo_part(info, _rc.part_name);
                        }

                        {
#ifndef _DOS
#pragma warning(suppress: 6386)
#endif
                            size_t read = fread(_rc.buff, 1, remaining_bytes, file);

                            if (ferror(file)) {
                                _exit_fail(RES_ERR_CANNOT_READ_FILE_1, path);
                                return FALSE;
                            }
                            else {
                                size_t written = fwrite(_rc.buff, 1, read, part);

                                if (written != read) {
                                    _exit_fail(RES_ERR_CANNOT_WRITE_FILE_1, _rc.part_name);
                                    return FALSE;
                                }

                                remaining_bytes -= read;
                                winfo_file(info, path, read);
                            }
                        }
                    } while (!feof(file));
                }
            }
        }
    }

    _free();
    return TRUE;
}
