#include "program.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "args.h"
#include "merge.h"
#include "res.h"
#include "split.h"
#include "utils.h"


const int main(const int argc, const char *const argv[]) {
    const CONFIG config = { 0 };
    parse_args((CONFIG *const)&config, argc, argv);

    if (config.mode == MODE_SPLIT) {
        split(&config);
    }
    else {
        merge(&config);
    }

    return EXIT_SUCCESS;
}

FILE *sfopen(const FMODE fmode) {
    if (HF(fmode, FMODE_EXISTING)) {

    }

    //fopen();
}

void *srealloc(void *const ptr, size_t *const size) {
    while (TRUE) {
        void *const new = realloc(ptr, *size);

        if (new != NULL) {
            return new;
        }

        *size = (size_t)(*size * 0.75);

        if (*size < 1) {
            return NULL;
        }
    }
}

void exit_fail(const BOOL _print_help, _Printf_format_string_ const char *const message_format, ...) {
    va_list args;
    va_start(args, message_format);
    vexit_fail(_print_help, message_format, args);
    va_end(args);
}

void vexit_fail(const BOOL _print_help, _Printf_format_string_ const char *const message_format, const va_list args) {
    if (message_format != NULL) {
        vfprintf(stderr, message_format, args);

        if (_print_help) {
            putc('\n', stdout);
        }
    }

    if (_print_help) {
        print_help();
    }

    fcloseall();
    exit(EXIT_FAILURE);
}
