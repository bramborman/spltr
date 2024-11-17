#ifndef PROGRAM_H
#define PROGRAM_H

#include <stdlib.h>
#include "utils.h"


#if defined(_DOS)
#define MAX_MEM    1000000
#elif defined(WIN32)
#define MAX_MEM  500000000
#else  /* x64 || ARM64 */
#define MAX_MEM 1500000000
#endif


#define EXT_INFO        ".spi"
#define EXT_INFO_LEN    4
#define EXT_PART        ".spp"
#define EXT_PART_LEN    4

#define HF(VALUE, FLAG) \
    (((VALUE & FLAG) == FLAG))


typedef enum {
    MODE_SPLIT,
    MODE_MERGE
} MODE;

typedef enum {
    /* Open file for read operations */
    FMODE_READ     = 0x1 << 0,
    /* Open file for write operations */
    FMODE_WRITE    = 0x1 << 1,
    /* Open only if the file already exists */
    FMODE_EXISTING = 0x1 << 2,
    /* Create the file, fail if it already exists */
    FMODE_CREATE   = 0x1 << 3
} FMODE;

/* Keep in sync with args.c/struct _CONFIG_M */
typedef struct {
    const char *const name;
    const size_t name_len;
    const MODE mode;
    const size_t split_size;
    /* const char *const cwd; */
    const char *const *const paths;
    const int path_count;
} CONFIG;


void *srealloc(void *const ptr, size_t *const size);
void exit_fail(const BOOL print_help, _Printf_format_string_ const char *const message_format, ...);
void vexit_fail(const BOOL print_help, _Printf_format_string_ const char *const message_format, const va_list args);

#endif /* !PROGRAM_H */
