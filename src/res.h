#ifndef RES_H
#define RES_H

#define LANG_ENG    0
#define LANG_CZE    1
#define LANG_CZE_D  2

#define LANG LANG_ENG
/* #define LANG LANG_CZE */
/* #define LANG LANG_CZE_D */

#if LANG == LANG_CZE
#error Not yet supported
#elif LANG == LANG_CZE_D
#define RES_ERR_UNKNOWN                     "Neznámá chyba."
#define RES_ERR_CANNOT_ALLOCATE             "Nepodařilo se naalokovat paměť. Nedostatek volné paměti RAM?"
#define RES_ERR_CANNOT_CREATE_FILE_1        "Nepodařilo se vytvořit soubor '%s'. Je možné, že už existuje."
#define RES_ERR_CANNOT_OPEN_FILE_1          "Nepodařilo se otevřít soubor '%s'."
#define RES_ERR_CANNOT_READ_FILE_1          "Nepodařilo se přečíst soubor '%s'."
#define RES_ERR_CANNOT_WRITE_FILE_1         "Nepodařilo se zapsat do souboru '%s'. Nedostatek místa na disku?"
#define RES_ARG_ERR_INVALID_ARG_COUNT_1     "Nesprávný počet argumentů: %d."
#define RES_ARG_ERR_INVALID_MODE_1          "Nesprávný režim '%s'."
#define RES_ARG_ERR_INVALID_TYPE_1          "Nesprávný typ '%s'."
#define RES_ARG_ERR_INVALID_SIZE_1          "Nesprávný formát velikosti '%s'."
#define RES_ARG_ERR_NO_PATHS_SPECIFIED      "Nebyly specifikovány žádné cesty."
#define RES_ARG_ERR_INVALID_DIR_COUNT_1     "Pouze jedna složka mùže být zpracována, ale bylo specifikováno %d."
#define RES_ARG_ERR_INVALID_PATH_2          "Cesta '%s' neexistuje, nebo není %s."
#define RES_ARG_SPLIT_SHORT                 "r"
#define RES_ARG_SPLIT_REST                  "ozdělit"
#define RES_ARG_MERGE_SHORT                 "s"
#define RES_ARG_MERGE_REST                  "pojit"
#define RES_ARG_DIR_SHORT                   "sl"
#define RES_ARG_DIR_REST                    "ožka"
#define RES_ARG_FILE_SHORT                  "so"
#define RES_ARG_FILE_REST                   "ubor"
#define RES_USG                             "Použití"
#define RES_USG_NAME                        "název"
#define RES_USG_SIZE                        "velikost"
#define RES_USG_DIR                         "složka"
#define RES_USG_FILE                        "soubor"
#define RES_USG_INFO                        "info"
#define RES_FILE                            "soubor"
#define RES_DIR                             "složka"
#define RES_PART                            "část"
#define RES_PART_LEN                        4
#else
#define RES_ERR_UNKNOWN                     "Unknown error."
#define RES_ERR_CANNOT_ALLOCATE             "Cannot allocate memory. Insufficient free RAM?"
#define RES_ERR_CANNOT_CREATE_FILE_1        "Cannot create file '%s'. It may already exist."
#define RES_ERR_CANNOT_OPEN_FILE_1          "Cannot open file '%s'."
#define RES_ERR_CANNOT_READ_FILE_1          "Cannot read file '%s'."
#define RES_ERR_CANNOT_WRITE_FILE_1         "Cannot write to file '%s'. Insufficient free disk space?"
#define RES_ARG_ERR_INVALID_ARG_COUNT_1     "Invalid argument count %d."
#define RES_ARG_ERR_INVALID_MODE_1          "Invalid mode '%s'."                                                    /* The parameter shows user input */
#define RES_ARG_ERR_INVALID_TYPE_1          "Invalid type '%s'."                                                    /* The parameter shows user input */
#define RES_ARG_ERR_INVALID_SIZE_1          "Invalid format of size '%s'."                                          /* The parameter shows user input */
#define RES_ARG_ERR_NO_PATHS_SPECIFIED      "No paths specified."
#define RES_ARG_ERR_INVALID_DIR_COUNT_1     "Only one directory can be processed but %d were specified."
#define RES_ARG_ERR_INVALID_FILE_COUNT_1    "Only one file can be processed but %d were specified."
#define RES_ARG_ERR_INVALID_PATH_2          "The path '%s' does not exist or is not a %s."                          /* Example: "The path 'C:\FOO\BAR' does not exist or is not a file." - The second parameter is RES_FILE or RES_DIR */
#define RES_ARG_SPLIT_SHORT                 "s"
#define RES_ARG_SPLIT_REST                  "plit"
#define RES_ARG_MERGE_SHORT                 "m"
#define RES_ARG_MERGE_REST                  "erge"
#define RES_ARG_DIR_SHORT                   "d"
#define RES_ARG_DIR_REST                    "irectory"
#define RES_ARG_FILE_SHORT                  "f"
#define RES_ARG_FILE_REST                   "ile"
#define RES_USG                             "Usage"
#define RES_USG_NAME                        "name"
#define RES_USG_SIZE                        "size"
#define RES_USG_DIR                         "directory"
#define RES_USG_FILE                        "file"
#define RES_USG_INFO                        "info"
#define RES_FILE                            "file"
#define RES_DIR                             "directory"
#define RES_PART                            "part"
#define RES_PART_LEN                        4
#endif

#endif /* !RES_H */
