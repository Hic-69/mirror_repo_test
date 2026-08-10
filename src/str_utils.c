/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** helpers function
*/

#include "../include/mysh.h"

static int is_in_reject(char c, const char *reject)
{
    int j = 0;

    while (reject[j] != '\0') {
        if (c == reject[j])
            return 1;
        j++;
    }
    return 0;
}

int my_strcspn(const char *str, const char *reject)
{
    int i = 0;

    while (str[i] != '\0') {
        if (is_in_reject(str[i], reject))
            return i;
        i++;
    }
    return i;
}

int my_strncmp(char const *s1, char const *s2, int size)
{
    int i = 0;

    while (i < size) {
        if (s1[i] != s2[i])
            return s1[i] - s2[i];
        i++;
    }
    return 0;
}

char *my_strdup(const char *str)
{
    char *dup = malloc(my_strlen(str) + 1);
    int i = 0;

    if (!dup)
        return NULL;
    for (i = 0; *(str + i) != '\0'; i++)
        *(dup + i) = *(str + i);
    *(dup + i) = '\0';
    return dup;
}

int my_strlen(const char *str)
{
    int i = 0;

    while (str[i] != '\0') {
        i++;
    }
    return i;
}

char *my_strcat(char *dest, const char *str)
{
    int i = 0;
    int j = 0;

    while (dest[i] != '\0')
        i++;
    while (str[j] != '\0') {
        dest[i] = str[j];
        i++;
        j++;
    }
    dest[i] = '\0';
    return dest;
}
