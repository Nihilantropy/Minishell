/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:05:55 by crea              #+#    #+#             */
/*   Updated: 2024/06/10 15:05:55 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	executor(t_shell *shell, char **envp)
{
	if (!ft_strcmp(shell->matrix[0], "here_doc"))
	{
		shell->here_doc = true;
		ft_here_doc(shell, envp);
		return ;
	}
	else
	{
		ft_pipex(shell, envp);
		return ;
	}
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
		printf(ERROR_EXECVE);
		return ;
	}
}

char	*find_cmd_path(t_shell *shell, char *command)
{
	int		i;
	char	*relative_path;
	char	*shell_path;

	i = 0;
	while (shell->env[i])
	{
		relative_path = ft_strjoin(shell->env[i], "/");
		shell_path = ft_strjoin(relative_path, command);
		free(relative_path);
		if (access(shell_path, F_OK) == 0)
		{
			free_matrix(shell->env);
			return (shell_path);
		}
		free(shell_path);
		i++;
	}
	free_matrix(shell->env);
	return (NULL);
}