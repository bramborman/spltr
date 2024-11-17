#include "utils.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>


size_t numlen(size_t num) {
    size_t count = 0UL;

    while (num >= 10UL) {
        count++;
        num /= 10UL;
    }

    return count;
}

BOOL streqci(const char *str1, const char *str2) {
    if (str1 == str2) {
        return TRUE;
    }
    else {
        int i;
        for (i = 0; ; i++) {
            char c1 = *(str1++);
            char c2 = *(str2++);

            if (c1 == c2) {
                if (c1 == '\0') {
                    return TRUE;
                }

                continue;
            }

            if (c1 == '\0' || c2 == '\0') {
                return FALSE;
            }

            if (tolower(c1) == tolower(c2)) {
                continue;
            }

            return FALSE;
        }
    }
}

BOOL strswci(const char *str1, const char *str2) {
    if (str1 == str2) {
        return TRUE;
    }
    else {
        int i;
        for (i = 0; ; i++) {
            char c1 = *(str1++);
            char c2 = *(str2++);

            if (c1 == c2) {
                if (c1 == '\0') {
                    return TRUE;
                }

                continue;
            }

            if (c1 == '\0') {
                return FALSE;
            }

            if (c2 == '\0') {
                return TRUE;
            }

            if (tolower(c1) == tolower(c2)) {
                continue;
            }

            return FALSE;
        }
    }
}

/*size_t strlici(const char *str, const char c) {
    const char *const start = str;
    size_t i = SIZE_INV;
    const char lc = (char)tolower(c);

    while (TRUE) {
        if (*str == '\0') {
            return i;
        }
        else if (*str == c || tolower(*str) == lc) {
            i = str - start;
        }

        str++;
    }
}*/

size_t eolpos(FILE *const file) {
    if (feof(file) || ferror(file)) {
        return SIZE_INV;
    }
    else {
        size_t pos = 0;

        while (TRUE) {
            char c = (char)fgetc(file);

            if (ferror(file)) {
                return SIZE_INV;
            }

            if (c == '\n' || feof(file)) {
                int res = fseek(file, -(long)pos, SEEK_CUR);

                if (IS_ERROR(res)) {
                    return SIZE_INV;
                }

                return pos;
            }

            pos++;
        }
    }
}

BOOL pcheck(const char *const path, const LEAFTYPE leaf_type) {
    struct stat statbuf;

    if (IS_ERROR(stat(path, &statbuf))) {
        return FALSE;
    }

    return
        (leaf_type == LEAFTYPE_FILE && S_ISREG(statbuf.st_mode))
        || (leaf_type == LEAFTYPE_DIR && S_ISDIR(statbuf.st_mode));
}