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

static void	count_pipes(t_shell *shell);
static void	find_last_index(t_shell *shell);
static void	find_limiter_index(t_shell *shell);

void	parse_args(t_shell *shell)
{
	shell->line = readline("minishell$ ");
	if (!shell->line)
		handle_eof();
	if (!shell->line[0])
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		free(shell->line);
		return ;
	}
	handle_history(shell);
	shell->matrix = ft_split(shell->line, ' ');
	count_pipes(shell);
	find_last_index(shell);
	find_limiter_index(shell);
	free(shell->line);
	return ;
}

static void	count_pipes(t_shell *shell)
{
	int	i;

	if (shell->matrix[0][0] == '|')
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		free_matrix(shell->matrix);
		return ;
	}
	i = 1;
	while (shell->matrix[i])
	{
		if (shell->matrix[i][0] == '|')
			shell->pipes_nbr++;
		i++;
	}
	printf("pipes number: %d\n", shell->pipes_nbr);
}

static void	find_last_index(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->matrix[i])
		i++;
	shell->last_index = i - 1;
	printf("last index: %d\n", shell->last_index);
}

static void	find_limiter_index(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->matrix[i])
	{
		if (!ft_strcmp(shell->matrix[i], "<<"))
		{
			shell->limiter_index = i + 1;
			return ;
		}
		i++;
	}
}
