/**
 * @file "StringFuncs.cpp"
 * @date 2026.09.08
 * @brief My functions to work with strings
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief takes string as const and returns it's len
 * @param [in] str string to count amount of args.
 * @return len of string as size_t. If ptr to NULL return 0
 */
size_t my_strlen(const char *str);

/**
 * @brief puts string to stdout and goes to new line.
 * @param [in] str string to put.
 * @return EOF in end of file or posetive number otherwise. If ptr to NULL return 0
 */
int my_puts(const char *str);

/**
 * @brief copyes one strind to another.
 * @param [out] dest string to copy in.
 * @param [in] str string to copy.
 * @return pointr to dest. If ptr to NULL return 0
 */
char *my_strcpy(char *dest, const char *str);

/**
 * @brief puts one string to end of another.
 * @param [out] dest string to put in.
 * @param [in] str string to be putted.
 * @return pointer to dest. If ptr to NULL return 0
 */
char *my_strcat(char *str, const char *ct);

/**
 * @brief compares strings. If same returns 0, if first bigger returns posetive number and negative otherwise.
 * @param [in] str1 frist string.
 * @param [in] str2 second string.
 * @return 0 if same, posetive if first is bigger and negative otherwise. If ptr to NULL return 0
 */
int my_strcmp(const char *str1, const char *str2);

/**
 * @brief works as my_strcpy but copyes n ells at max. if str.len less then n left space will be zeros
 * @param [out] dest string to copy in.
 * @param [in] str string to copy.
 * @param [in] n amount of symbols to copy.
 * @return pointer to dest. If ptr to NULL return 0
 */
char *my_strncpy(char *dest, const char *str, size_t n);

/**
 * @brief works as my_strcar but limited on n symbols. 
 * @param [out] dest string to put in.
 * @param [in] str string to be putted.
 * @param [in] n max symbols to be putted.
 * @return pointer to dest. If ptr to NULL return 0
 */
char *my_strncat(char *str, char *ct, size_t n);

/**
 * @brief works as my_strcmp but checks only first n symbols. 
 * @param [in] str1 frist string.
 * @param [in] str2 second string.
 * @param [in] n max symbols to compare.
 * @return 0 if same, posetive if first is bigger and negative otherwise. If ptr to NULL return 0
 */
int my_strncmp(const char *str1, const char *str2, size_t n);

/**
 * @brief copyes string to dynamic mamory and returns pointer to it.
 * @param [in] str string to copy.
 * @return pointer to first element of new string. If ptr to NULL return 0
 */
char *my_strdup(const char *str);

/**
 * @brief works as my_strdup but copyes only n(or less) symbols.
 * @param [in] str string to copy.
 * @param [in] n max amount of ells to copy.
 * @return pointer to first element of new string. If ptr to NULL return 0
 */
char *my_strndup(const char *str, size_t n);

/**
 * @brief macros to find minimum ell.
 */
#define min(a, b) ((a) > (b) ? (b) : (a))

size_t my_strlen(const char *str)
{
    if (str == NULL) {
        printf("SORRY, WRONG INPUT");
        return 0;
    }
    size_t len = 0;

    while (str[len] != '\0') {
        len++;
    }
    return len;
}

int main()
{
    printf("%d", my_strcmp("abc", "abc "));
}

int my_puts(const char *str)
{
    if (str == NULL) {
        printf("SORRY, WRONG INPUT");
        return 0;
    }

    for (size_t i = 0; str[i] != '\0'; i++) {
        if (putchar(str[i]) == EOF) {
            return EOF;
        }
    }

    putchar('\n');
    return 1;
}

char *my_strcpy(char *dest, const char *str)
{
    if (str == NULL || dest == NULL) {
        printf("SORRY, WRONG INPUT");
        return 0;
    }

    size_t ind = 0;

    while(str[ind] != '\0') {
        dest[ind] = str[ind];
        ind++;
    }

    dest[ind] = '\0';
    return dest;
}

char *my_strcat(char *str, const char *ct)
{
    if (str == NULL || ct == NULL) {
        printf("SORRY, WRONG INPUT");
        return 0;
    }

    size_t i = 0;
    while (str[i] != '\0')
        i++;
    
    for (size_t j = 0; ct[j] != '\0'; j++, i++) {
        str[i] = ct[j];
    }

    str[i] = '\0';
    return str;
}

int my_strcmp(const char *str1, const char *str2)
{
    if (str1 == NULL || str2 == NULL) {
        printf("SORRY, WRONG INPUT");
        return 0;
    }
    size_t i = 0;

    while(str1[i] != '\0' && str1[i] == str2[i]) 
       i++; 

    return str1[i] - str2[i];
}

char *my_strncpy(char *dest, const char *str, size_t n)
{
    if (str == NULL || dest == NULL) {
        printf("SORRY, WRONG INPUT");
        return 0;
    }

    size_t i = 0;

    while(str[i] != '\0' && i < n) {
        dest[i] = str[i];
        i++;
    }

    while (i < n)
        dest[i++] = '\0';

    return dest;
}

char *my_strncat(char *str, const char *ct, size_t n)
{
    if (str == NULL || ct == NULL) {
        printf("SORRY, WRONG INPUT");
        return 0;
    }

    size_t i = 0;
    while (str[i] != '\0')
        i++;
    
    for (int j = 0; ct[j] != '\0' && j < n; j++, i++) {
        str[i] = ct[j];
    }

    str[i] = '\0';
    return str;
}

int my_strncmp(const char *str1, const char *str2, size_t n)
{
    if (str1 == NULL || str2 == NULL) {
        printf("SORRY, WRONG INPUT");
        return 0;
    }

    size_t i = 0;
    if (n == 0) return 0; // in this case all strings are same;

    while (i < n && str1[i] != '\0' && str1[i] == str2[i])
        i++;
    
    return str1[i] - str2[i];
}
    
char *my_strdup(const char *str)
{
    if (str == NULL) {
        printf("SORRY, WRONG INPUT");
        return 0;
    }

    size_t len = my_strlen(str);

    char *ans = (char *) calloc(len + 1, sizeof(char));

    if (ans == NULL) {
        printf("SORRY, NOT ENOUGHT MEMORY");
        return NULL;
    }

    return my_strcpy(ans, str);
}

char *my_strndup(const char *str, size_t n)
{
    if (str == NULL) {
        printf("SORRY, WRONG INPUT");
        return 0;
    }

    size_t len = my_strlen(str);

    char *ans = (char *) calloc(min(len, n) + 1, sizeof(char));

    if (ans == NULL) {
        printf("NOT ENOUGHT MEMORY");
        return NULL;
    }

    return my_strncpy(ans, str, min(len, n));
}
