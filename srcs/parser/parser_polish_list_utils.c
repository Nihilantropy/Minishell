/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_polish_list_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:45:09 by crea              #+#    #+#             */
/*   Updated: 2024/09/23 13:45:10 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_token_index(t_shell *shell);
static void	syntax_error_near_token(t_shell *shell, char *str);

int	check_arg_list(t_shell *shell)
{
	if (shell->arg->token.pipe)
	{
		printf("-minishell: syntax error near unexpected token `%s'\n", shell->arg->str);
		g_exit_status = 2;
		shell->error = true;
		return (1);
	}
	if (check_token_index(shell))
		return (1);
	return (0);
}

static int	check_token_index(t_shell *shell)
{
	t_arg	*current_node;
	t_arg	*next_node;

	current_node = shell->arg;
	while (current_node)
	{
		next_node = current_node->next;
		if (current_node->token.is_token && !next_node)
		{
			syntax_error_near_token(shell, current_node->str);
			return (1);
		}
		else if (next_node && ((current_node->token.is_token && !current_node->token.pipe) 
					&& next_node->token.is_token))
		{
			syntax_error_near_token(shell, next_node->str);
			return (1);
		}
		current_node = current_node->next;
	}
	return (0);
}

static void	syntax_error_near_token(t_shell *shell, char *str)
{
	ft_putstr_fd("-minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("'\n", 2);
	g_exit_status = 2;
	shell->error = true;
}
