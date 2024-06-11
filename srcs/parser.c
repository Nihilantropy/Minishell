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
	shell->matrix = ft_split(shell->line, '|');
	count_pipes(shell);
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
	i = 0;
	while (shell->matrix[i])
		i++;
	shell->cmd.pipes_nbr = i - 1;
	printf("pipes number: %d\n", shell->cmd.pipes_nbr);
}
