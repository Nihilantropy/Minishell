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

void	exe_cmd(t_shell *shell, char *command, char **envp)
{
	char	*path;
	char	**total_command;

	total_command = ft_split(command, ' ');
	path = find_cmd_path(shell, total_command[0]);
	if (!path)
	{
		free_matrix(total_command);
		return ;
	}
	if (execve(path, total_command, envp) == -1)
	{
		perror("execve");
		free_matrix(total_command);
		free(path);
		exit(EXIT_FAILURE);
	}
}

char	*find_cmd_path(t_shell *shell, char *command)
{
	int		i;
	char	*relative_path;
	char	*cmd_path;

	i = 0;
	while (shell->env[i])
	{
		relative_path = ft_strjoin(shell->env[i], "/");
		cmd_path = ft_strjoin(relative_path, command);
		free(relative_path);
		if (access(cmd_path, F_OK) == 0)
		{
			free_matrix(shell->env);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	free_matrix(shell->env);
	return (NULL);
}