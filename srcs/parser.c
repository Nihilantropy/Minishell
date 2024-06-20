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

static int	arg_length(char *line)
{
	int		i;
	char	quote;

	i = 0;
	if (line[0] == '\"' || line[0] == '\'')
	{
		i++;
		quote = line[0];
		while (line[i] != quote)
			i++;
		return (i);
	}
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		i++;
	return (i);
}

static void	append_node(t_arg **arg, t_arg *new_node)
{
	t_arg	*last_node;

	last_node = find_last_node(*arg);
	if (!*arg)
	{
		*arg = new_node;
		new_node->prev = new_node;
	}
	else
	{
		last_node->next = new_node;
		new_node->prev = last_node;
	}
}

static void	create_new_node(t_arg **arg, char *line)
{
	int		i;
	int		len;
	t_arg	*new_node;

	if (!line)
		return ;
	i = 0;
	len = 0;
	new_node = malloc(sizeof(t_arg));
	if (!new_node)
		ft_exit_error(ERR_NODE_ALLOC);
	len = arg_length(line);
	new_node->str = malloc(len + 1);
	if (!new_node->str)
		ft_exit_error(ERR_STR_NODE_ALLOC);
	while (line[i] && line[i] != ' ')
	{
		new_node->str[i] = line[i];
		i++;
	}
	new_node->next = NULL;
	append_node(arg, new_node);

} 

static void	parse_list(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->line[i])
	{
		while (shell->line[i] == ' ' || shell->line[i] == '\t')
			i++;
		create_new_node(&shell->arg, shell->line + i);
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
