/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:45:17 by crea              #+#    #+#             */
/*   Updated: 2024/09/23 15:17:00 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	quote_node_length(char *temp, t_arg *new_node);
static int	none_quote_node_length(char *temp, t_arg *new_node);

/*	arg length:
**	Find the length of the node string argument
*/
int	arg_length(char *temp, t_arg *new_node)
{
	int		i;

	i = 0;
	if (temp[0] == '\"' || temp[0] == '\'')
		i = quote_node_length(temp, new_node);
	else
		i = none_quote_node_length(temp, new_node);
	return (i);
}

/*	token legth:
**	Find the length of the node token argument.
*/
int	token_length(char *temp)
{
	char	token;

	token = *temp;
	if (token == '|')
		return (1);
	else if (token == '<' || token == '>')
	{
		if (temp[1] == token)
			return (2);
		else
			return (1);
	}
	return (0);
}

/*	auote node length:
**	Return the length of the quoted argument and activate the 'chained'
**	flag if the node is chained to the next one.
*/
static int	quote_node_length(char *temp, t_arg *new_node)
{
	int		i;
	char	quote;

	i = 1;
	quote = *temp;
	while (temp[i] != quote && temp[i])
		i++;
	if (temp[i + 1])
	{
		if (temp[i + 1] != ' ' && temp[i + 1] != '\t')
			new_node->chained = true;
	}
	return (i);
}

/*	none quote node length:
**	Return the length of the non-quoted argument and activate the 'chained'
**	flag if the node is chained to the next one.
*/
static int	none_quote_node_length(char *temp, t_arg *new_node)
{
	int	i;

	i = 0;
	while ((temp[i] != '\'' && temp[i] != '\"'
			&& temp[i] != '>' && temp[i] != '<'
			&& temp[i] != '|' && temp[i] != ' '
			&& temp[i] != '\t') && temp[i])
		i++;
	if (temp[i])
	{
		if (temp[i] != ' ' && temp[i] != '\t')
			new_node->chained = true;
	}
	return (i);
}
