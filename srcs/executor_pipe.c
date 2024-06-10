/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:18:57 by crea              #+#    #+#             */
/*   Updated: 2024/06/10 15:18:57 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_here_doc(t_shell *shell, char **envp)
{
	int		here_doc;
	int		write_file;
	char	*line;

	here_doc = open(".here_doc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (here_doc == -1)
		ft_exit_error(ERROR_OPEN_FILE);
	while (1)
	{
		ft_putstr_fd("heredoc> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			return (0);
		ft_putstr_fd(line, here_doc);
		if (!ft_strcmp(ft_strtrim(line, " \t\n\r\v"), shell->matrix[shell->limiter_index]))
			break ;
		free(line);
	}
	free(line);
	dup2(here_doc, STDIN_FILENO);
	write_file = open(shell->matrix[shell->last_index], O_WRONLY | O_CREAT | O_APPEND, 0600);
	if (write_file == -1)
		ft_exit_error(ERROR_WRITE_FILE);
	while (shell->index < shell->pipes_nbr)
		process_child(shell, shell->matrix[shell->index++], envp);
	wait(NULL);
	unlink(".here_doc.tmp");
	dup2(write_file, STDOUT_FILENO);
	process_parent(shell, shell->matrix[shell->index], envp);
	return (0);
}

void	ft_pipex(t_shell *shell, char **envp)
{
	int		read_file;
	int		write_file;

	read_file = open(shell->matrix[0], O_RDONLY, 0777);
	if (read_file == -1)
		return ;
	dup2(read_file, STDIN_FILENO);
	write_file = open(shell->matrix[shell->last_index], O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (write_file == -1)
		return ;
	while (shell->index < shell->pipes_nbr)
		process_child(shell, shell->matrix[shell->index++], envp);
	wait(NULL);
	dup2(write_file, STDOUT_FILENO);
	process_parent(shell, shell->matrix[shell->index], envp);
	return ;
}

void	process_child(t_shell *shell, char *command, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		ft_exit_error(PIPE_ERROR);
	pid = fork();
	if (pid == -1)
		ft_exit_error(FORK_ERROR);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		exe_cmd(shell, command, envp);
	}
	else
	{
		waitpid(pid, NULL, 0);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		return ;
	}
}

void	process_parent(t_shell *shell, char *command, char **envp)
{
	exe_cmd(shell, command, envp);
}