#ifndef INFO_H
#define INFO_H

#include <stdio.h>


void winfo_part(FILE *const info, const char *const part_name);
void winfo_file(FILE *const info, const char *const file_name, const size_t file_bytes);
void rinfo(FILE *const info, const char *const *part_name, const char *const *file_name, size_t *file_bytes);

#endif /* !INFO_H */
