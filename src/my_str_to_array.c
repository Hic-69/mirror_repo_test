/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** split function
*/

#include "../include/mysh.h"

static int count_words(char *str, char sep)
{
    int count = 0;
    int in_word = 0;

    while (*str) {
        if (*str == sep && in_word)
            in_word = 0;
        if (*str != sep && !in_word) {
            in_word = 1;
            count++;
        }
        str++;
    }
    return count;
}

static char *fill_word(char *str, char sep)
{
    char *word;
    int j = 0;

    while (str[j] && str[j] != sep)
        j++;
    word = malloc(sizeof(char) * (j + 1));
    if (!word)
        return NULL;
    word[j] = 0;
    while (j > 0) {
        j--;
        word[j] = str[j];
    }
    return word;
}

static void free_array(char **array)
{
    int i = 0;

    while (array[i]) {
        free(array[i]);
        i++;
    }
    free(array);
}

static char **fill_array(char **array, char *str, char sep, int words)
{
    int i = 0;

    while (i < words) {
        while (*str == sep)
            str++;
        array[i] = fill_word(str, sep);
        if (!array[i]) {
            free_array(array);
            return NULL;
        }
        while (*str && *str != sep)
            str++;
        i++;
    }
    array[i] = NULL;
    return array;
}

char **my_str_to_array(char *str, char sep)
{
    int words = count_words(str, sep);
    char **array = malloc(sizeof(char *) * (words + 1));

    if (!array)
        return NULL;
    return fill_array(array, str, sep, words);
}
