/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_plus_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:18:54 by crea              #+#    #+#             */
/*   Updated: 2024/06/12 16:18:54 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static t_bool is_double_separator(const char *str, const char *sep_set)
{
	while (*sep_set)
	{
		if (str[0] == *sep_set && str[1] == *sep_set)
			return (true);
		sep_set++;
	}
	return (false);
}

static int count_tokens(const char *str, const char *sep_set)
{
	int count;
	int in_word;
	
	count = 0;
	in_word = 0;
	while (*str)
	{
		if (is_double_separator(str, sep_set))
		{
			count++;
			str += 2;
			in_word = 0;
		}
		else if (is_separator(*str, sep_set))
		{
			count++;
			str++;
			in_word = 0;
		}
		else if (!in_word)
		{
			in_word = 1;
			count++;
			str++;
		}
		else
			str++;
	}
	return (count);
}

static char *alloc_token(const char **str, const char *sep_set)
{
	int		len;
	char	*token;
	
	len = 0;
	if (is_double_separator(*str, sep_set))
	{
		token = (char *)malloc(3);
		if (!token)
			return (NULL);
		token[0] = (*str)[0];
		token[1] = (*str)[1];
		token[2] = '\0';
		*str += 2;
		return (token);
	}
	if (is_separator(**str, sep_set))
	{
		token = (char *)malloc(2);
		if (!token)
			return (NULL);
		token[0] = **str;
		token[1] = '\0';
		(*str)++;
		return (token);
	}
	while ((*str)[len] && !is_separator((*str)[len], sep_set) &&
			!is_double_separator(*str + len, sep_set))
		len++;
	token = (char *)malloc(len + 1);
	if (!token)
		return (NULL);
	ft_strlcpy(token, *str, len);
	token[len] = '\0';
	*str += len;
	return (token);
}

char **ft_split_plus_utils(const char *str, const char *sep_set)
{
	int		tokens_nbr;
	char	**matrix;
	int		i;

	if (!str || !sep_set)
		return (NULL);
	tokens_nbr = count_tokens(str, sep_set);
	matrix = (char **)malloc(sizeof(char *) * (tokens_nbr + 1));
	if (!matrix)
		return (NULL);
	i = 0;
	while (*str)
	{
		if ((is_separator(*str, sep_set) || is_double_separator(str, sep_set)) ||
			(*str && !is_separator(*str, sep_set) && !is_double_separator(str, sep_set)))
		{
			matrix[i] = alloc_token(&str, sep_set);
			if (!matrix[i])
			{
				while (i > 0)
					free(matrix[--i]);
				free(matrix);
				return (NULL);
			}
			i++;
		}
	}
	matrix[i] = NULL;
	return (matrix);
}