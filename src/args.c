#include "args.h"

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "program.h"
#include "res.h"
#include "utils.h"


/* Keep in sync with program.h/CONFIG */
struct _CONFIG_M {
    const char *name;
    size_t name_len;
    MODE mode;
    size_t split_size;
    const char *const *paths;
    int path_count;
};


#define _arg_named(arg_short, arg_rest) arg_short"("arg_rest")"
#define _arg_value(arg_name) "<"arg_name">"


void print_help(void) {
    printf(RES_USG":");
    printf("\n  spltr "_arg_named(RES_ARG_SPLIT_SHORT, RES_ARG_SPLIT_REST)" "_arg_value(RES_USG_NAME)" "_arg_value(RES_USG_SIZE)" "_arg_named(RES_ARG_DIR_SHORT, RES_ARG_DIR_REST)" "_arg_value(RES_USG_DIR));
    printf("\n  spltr "_arg_named(RES_ARG_SPLIT_SHORT, RES_ARG_SPLIT_REST)" "_arg_value(RES_USG_NAME)" "_arg_value(RES_USG_SIZE)" "_arg_named(RES_ARG_FILE_SHORT, RES_ARG_FILE_REST)" "_arg_value(RES_USG_FILE"1")" ["_arg_value(RES_USG_FILE"2")" "_arg_value(RES_USG_FILE"3")" ...]");
    printf("\n  spltr "_arg_named(RES_ARG_MERGE_SHORT, RES_ARG_MERGE_REST)" "_arg_value(RES_USG_FILE""EXT_INFO));
}

void parse_args(CONFIG *const _config, const int _argc, const char *const _argv[]) {
    /* Ignore the exe name */
    const int argc = _argc - 1;
    const char *const *const argv = &_argv[1];

    if (argc < 2) {
        exit_fail(TRUE, argc != 0 ? RES_ARG_ERR_INVALID_ARG_COUNT_1 : NULL, argc);
        return;
    }
    else {
        struct _CONFIG_M *const config = (struct _CONFIG_M *const)_config;

        if (config == NULL) {
            exit_fail(FALSE, RES_ERR_CANNOT_ALLOCATE);
            return;
        }
        else {
            const char *const arg_mode = argv[0];
            int pi = -1;
            LEAFTYPE type;

            if (strswci(RES_ARG_SPLIT_SHORT""RES_ARG_SPLIT_REST, arg_mode)) {
                config->mode = MODE_SPLIT;
                pi = 1;

                {
                    config->name = argv[pi++];
                    config->name_len = strlen(config->name);
                }
                {
                    const char *const arg_size = argv[pi++];

                    if (sscanf(arg_size, "%zu", &config->split_size) != 1 || config->split_size <= 0) {
                        exit_fail(TRUE, RES_ARG_ERR_INVALID_SIZE_1, arg_size);
                        return;
                    }
                }
                {
                    const char *const arg_type = argv[pi++];

                    if (strswci(RES_ARG_FILE_SHORT""RES_ARG_FILE_REST, arg_type)) {
                        type = LEAFTYPE_FILE;
                    }
                    else if (strswci(RES_ARG_DIR_SHORT""RES_ARG_DIR_REST, arg_type)) {
                        type = LEAFTYPE_DIR;
                    }
                    else {
                        exit_fail(TRUE, RES_ARG_ERR_INVALID_TYPE_1, arg_type);
                        return;
                    }
                }
            }
            else if (strswci(RES_ARG_MERGE_SHORT""RES_ARG_MERGE_REST, arg_mode)) {
                config->mode = MODE_MERGE;
                type = LEAFTYPE_FILE;
                pi = 1;
            }
            else {
                exit_fail(TRUE, RES_ARG_ERR_INVALID_MODE_1, arg_mode);
                return;
            }

            config->path_count = argc - pi;

            if (config->path_count == 0) {
                exit_fail(TRUE, RES_ARG_ERR_NO_PATHS_SPECIFIED);
                return;
            }

            if (type == LEAFTYPE_DIR && config->path_count != 1) {
                exit_fail(TRUE, RES_ARG_ERR_INVALID_DIR_COUNT_1, config->path_count);
                return;
            }

            if (config->mode == MODE_MERGE && config->path_count != 1) {
                exit_fail(TRUE, RES_ARG_ERR_INVALID_FILE_COUNT_1, config->path_count);
                return;
            }

            config->paths = &argv[pi];

            for (; pi < argc; pi++) {
                const char *const arg = argv[pi];

                if (!pcheck(arg, type)) {
                    const char *const type_res = type == LEAFTYPE_FILE ? RES_FILE : RES_DIR;
                    exit_fail(FALSE, RES_ARG_ERR_INVALID_PATH_2, arg, type_res);
                    return;
                }
            }

            if (type == LEAFTYPE_DIR) {
                /* TODO: Convert to FILES */
                exit_fail(FALSE, "Directory is not yet supported.");
                return;
            }
        }
    }
}