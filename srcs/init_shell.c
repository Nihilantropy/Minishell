/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:34:41 by crea              #+#    #+#             */
/*   Updated: 2024/06/07 12:34:41 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	**find_total_path(char **envp);

void	init_shell(t_shell *shell, char **envp)
{
	shell->fd = STDIN_FILENO;
	shell->line = NULL;
	shell->matrix = NULL;
	shell->cmd.pipes_nbr = -1;
	shell->cmd.index = 0;
	shell->cmd.redir.redirection = false;
	shell->cmd.redir.here_doc = false;
	shell->cmd.redir.limiter_index = 0;
	shell->env = find_total_path(envp);
	shell->fd_input = dup(STDIN_FILENO);
	shell->fd_output = dup(STDOUT_FILENO);
}

static char	**find_total_path(char **envp)
{
	char	**total_path;
	int		i;

	i = 0;
	while (!ft_strnstr(envp[i], "PATH=", 5))
		i++;
	total_path = ft_split(envp[i] + 5, ':');
	return (total_path);
}
