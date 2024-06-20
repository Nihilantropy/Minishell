/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:12:46 by crea              #+#    #+#             */
/*   Updated: 2024/06/07 16:12:46 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_arg	*find_last_node(t_arg *arg);

static int	arg_length(char *temp)
{
	int		i;
	char	quote;

	i = 0;
	if (temp[0] == '\"' || temp[0] == '\'')
	{
		i++;
		quote = temp[0];
		while (temp[i] != quote && temp[i])
			i++;
		return (i + 1);
	}
	while (temp[i] && temp[i] != ' ' && temp[i] != '\t')
		i++;
	return (i);
}

static void	append_node(t_arg **arg, t_arg *new_node)
{
	t_arg	*last_node;

	if (!*arg)
	{
		*arg = new_node;
		new_node->prev = new_node;
	}
	else
	{
		last_node = find_last_node(*arg);
		last_node->next = new_node;
		new_node->prev = last_node;
	}
	new_node->next = NULL;
}

static char	*create_quote_node(t_arg **arg, char *temp)
{
	char	quote;
	int		len;
	t_arg	*new_node;

	quote = *temp;
	len = arg_length(temp);
	new_node = (t_arg *)malloc(sizeof(t_arg));
	if (!new_node)
		ft_exit_error("ERR_MALLOC");
	new_node->str = (char *)malloc(len - 1);
	if (!new_node->str)
		ft_exit_error("ERR_MALLOC");
	ft_strlcpy(new_node->str, temp + 1, len - 1);
	if (quote == '\'')
		new_node->quote = QUOTE_SINGLE;
	else
		new_node->quote = QUOTE_DOUBLE;
	append_node(arg, new_node);
	return (temp + len);
}

static char	*create_new_node(t_arg **arg, char *temp)
{

} 

static void	parse_list(t_shell *shell)
{
	char	*temp;
	char	*original_temp;

	temp = ft_strdup(shell->line);
	if (!temp)
		ft_exit_error("ERR_MALLOC");
	original_temp = temp;
	while (*temp)
	{
		if (*temp == '\'' || *temp == '\"')
		{
			temp = create_quote_node(&shell->arg, temp);
			if (temp == NULL)
				break ;
		}
		else if (*temp != ' ' && *temp != '\t')
		{
			temp = create_new_node(&shell->arg, temp);
			if (temp == NULL)
				break ;
		}
		else
			temp++;
	}
}

void	parse_args(t_shell *shell)
{
	shell->line = readline("minishell$ ");
	if (!shell->line)
		handle_eof();
	if (!shell->line[0])
	{
		handle_enter(shell);
		return ;
	}
	parse_list(shell);
	handle_history(shell);
	free(shell->line);
	return ;
}
