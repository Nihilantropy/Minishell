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

/*
	Init the main shell struct
*/
void	init_shell(t_shell *shell, char **envp)
{
	shell->fd = STDIN_FILENO;
	shell->line = NULL;
	shell->add_to_history = true;
	shell->arg = NULL;
	shell->pipes_nbr = 0;
	shell->env = NULL;
	init_env(shell, envp);
	shell->path = find_total_path(envp);
	shell->last_exit_status = 0;
	shell->cmd = NULL;
}

/*
	Find the PATH for the executable
*/
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