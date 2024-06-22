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

static char	*create_quote_node(t_arg **arg, char *temp)
{
	char	quote;
	int		len;
	t_arg	*new_node;

	quote = *temp;
	new_node = init_new_node();
	len = arg_length(temp);
	new_node->str = (char *)malloc(len);
	if (!new_node->str)
		ft_exit_error("ERR MALLOC STR QUOTE");
	ft_strlcpy(new_node->str, temp + 1, len);
	if (quote == '\'')
		new_node->quote.SINGLE = true;
	else if (quote == '\"')
		new_node->quote.DOUBLE = true;
	struct_list(arg, new_node);
	return (temp + len + 1);
	// TODO Do not handle the unclosed quote. Have to see waht does it mena.
	// For now it just create a quoted node.
}

static char	*create_token_node(t_arg **arg, char *temp)
{
	int		len;
	t_arg	*new_node;

	new_node = init_new_node();
	len = token_length(temp);
	new_node->str = (char *)malloc(len + 1);
	if (!new_node->str)
		ft_exit_error("ERR MALLOC STR TOKEN");
	ft_strlcpy(new_node->str, temp, len + 1);
	if (!ft_strcmp(new_node->str, "|"))
		new_node->token.pipe = true;
	else if (ft_strcmp(new_node->str, "<"))
		new_node->token.infile = true;
	else if (ft_strcmp(new_node->str, ">"))
		new_node->token.outfile = true;
	else if (ft_strcmp(new_node->str, "<<"))
		new_node->token.here_doc = true;
	else if (ft_strcmp(new_node->str, ">>"))
		new_node->token.append = true;
	new_node->quote.NONE = true;
	struct_list(arg, new_node);
	return (temp + len);
}

static char	*create_new_node(t_arg **arg, char *temp)
{
	int		len;
	t_arg	*new_node;

	new_node = init_new_node();
	len = arg_length(temp);
	new_node->str = (char *)malloc(len + 1);
	if (!new_node->str)
		ft_exit_error("ERR MALLOC STR");
	ft_strlcpy(new_node->str, temp, len + 1);
	new_node->quote.NONE = true;
	struct_list(arg, new_node);
	return (temp + len);
}

static void	parse_list(t_shell *shell)
{
	char	*temp;
	char	*original_temp;

	temp = ft_strdup(shell->line);
	original_temp = temp;
	while (*temp)
	{
		if (!*temp)
			break ;
		if (*temp == '\'' || *temp == '\"')
			temp = create_quote_node(&shell->arg, temp);
		else if (*temp == '|' || *temp == '<' || *temp == '>')
			temp = create_token_node(&shell->arg, temp);
		else if (*temp != ' ' && *temp != '\t' && *temp != '|'
				&& *temp != '<' && *temp != '>')
			temp = create_new_node(&shell->arg, temp);
		else
			temp++;
	}
	print_list(shell->arg);
	free(original_temp);
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
