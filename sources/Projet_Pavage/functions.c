//
// Created by mathi on 09/06/2024.
//

#include <string.h>
#include "functions.h"
/**
 * La fonction permet de retirer le caractère "\n" d'un string
 *
 * @param str Le string dont on souhaite retirer le caractère "\n" est passé en paramètre
 */
void trim_newline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && (str[len - 1] == '\n' || str[len - 1] == '\r')) {
        str[len - 1] = '\0';
    }
}