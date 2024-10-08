/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:44:09 by crea              #+#    #+#             */
/*   Updated: 2024/09/24 14:12:35 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_process(t_shell *shell);
static void	process_pipeline(t_shell *shell, t_cmd *current_node, int fd[2]);

/*	process command:
**	use the pipe to syncronyze the
**	processes in the pipeline.
*/
void	process_command(t_shell *shell)
{
	int		status;

	handle_process(shell);
	while (wait(&status) > 0)
		g_exit_status = handle_exit_status(status);
	free_shell(shell);
	free_prompt(shell);
	exit(g_exit_status);
}

static void	handle_process(t_shell *shell)
{
	int		fd[2];
	t_cmd	*current_node;
	pid_t	pid;

	current_node = shell->cmd;
	while (current_node)
	{
		if (pipe(fd) == -1)
			ft_exit_error(ERR_PIPE);
		pid = fork();
		if (pid == -1)
			ft_exit_error(ERR_FORK);
		if (pid == 0)
			process_pipeline(shell, current_node, fd);
		else
		{
			close(fd[1]);
			if (current_node->next)
				dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			current_node = current_node->next;
		}
	}
	close(STDIN_FILENO);
}

/*	process pipeline:
**	redirect input & output and execute
**	command or builtins
*/
static void	process_pipeline(t_shell *shell, t_cmd *current_node, int fd[2])
{
	if (current_node->next)
		dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	redir_input(current_node->redir);
	redir_output(current_node->redir);
	if (current_node->builtin.is_builtin)
	{
		handle_builtin(shell, current_node);
	}
	else if (current_node->matrix[0])
		exe_cmd(shell, current_node);
	else
		ft_exit_error("");
	free_shell(shell);
	free_prompt(shell);
	exit(EXIT_SUCCESS);
}
