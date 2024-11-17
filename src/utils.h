#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <sys/stat.h>


#define BOOL    int
#define TRUE    1
#define FALSE   0

#if (!defined(S_ISREG) || !defined(S_ISDIR)) && !defined(__S_ISTYPE) && defined(S_IFMT)
#define __S_ISTYPE(mode, mask)      (((mode) & S_IFMT) == (mask))
#endif
#if !defined(S_ISREG) && defined(S_IFREG)
#define S_ISREG(mode)               __S_ISTYPE((mode), S_IFREG)
#endif
#if !defined(S_ISDIR) && defined(S_IFDIR)
#define S_ISDIR(mode)               __S_ISTYPE((mode), S_IFDIR)
#endif

#if !defined(_Printf_format_string_)
#define _Printf_format_string_
#endif

#define IS_SUCCESS(x) ((x) == 0)
#define IS_ERROR(x) ((x) != 0)

#define SIZE_INV ((size_t)-1)


typedef enum {
    LEAFTYPE_FILE,
    LEAFTYPE_DIR
} LEAFTYPE;


/* NUMberLENgth */
size_t numlen(size_t num);
/* STRingsEQualCaseInsensitive */
BOOL streqci(const char *str1, const char *str2);
/* STRingStartsWithCaseInsensitive */
BOOL strswci(const char *str1, const char *str2);
/* STRingLastIndexCaseInsensitive */
/*size_t strlici(const char *str, const char c);*/
/* EndOfLinePOSition */
size_t eolpos(FILE *const file);
/* PathCHECK */
BOOL pcheck(const char* const path, const LEAFTYPE leaf_type);

#endif /* !UTILS_H */
