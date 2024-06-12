#include "../include/minishell.h"

static t_bool is_separator(char c, const char *sep_set)
{
	while (*sep_set)
	{
		if (c == *sep_set)
			return (true);
		sep_set++;
	}
	return (false);
}

static int count_words(const char *str, const char *sep_set)
{
	int count = 0;
	int in_word = 0;

	while (*str)
	{
		if (is_separator(*str, sep_set))
		{
			in_word = 0;
		}
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		str++;
	}
	return (count);
}

static char *alloc_word(const char *str, const char *sep_set)
{
	int len = 0;
	while (str[len] && !is_separator(str[len], sep_set))
		len++;
	
	char *word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	
	for (int i = 0; i < len; i++)
		word[i] = str[i];
	
	word[len] = '\0';
	return (word);
}

char **ft_split_plus(const char *str, const char *sep_set)
{
	if (!str || !sep_set)
		return (NULL);

	int words_nbr = count_words(str, sep_set);
	char **matrix = (char **)malloc(sizeof(char *) * (words_nbr + 1));
	if (!matrix)
		return (NULL);
	int i = 0;
	while (*str)
	{
		while (*str && is_separator(*str, sep_set))
			str++;
		if (*str && !is_separator(*str, sep_set))
		{
			matrix[i] = alloc_word(str, sep_set);
			if (!matrix[i])
			{
				while (i > 0) free(matrix[--i]);
				free(matrix);
				return (NULL);
			}
			i++;
		}
		while (*str && !is_separator(*str, sep_set))
			str++;
	}
	matrix[i] = NULL;
	return (matrix);
}
