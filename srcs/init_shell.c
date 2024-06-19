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
	shell->add_to_history = true;
	shell->arg->index = -1;
	shell->arg->quote = QUOTE_NONE;
	shell->arg->token.is_token = false;
	shell->arg->token.infile = false;
	shell->arg->token.outfile = false;
	shell->arg->token.append = false;
	shell->arg->token.here_doc = false;
	shell->arg->str = NULL;
	shell->arg->next = NULL;
	shell->arg->prev = NULL;
	shell->env = find_total_path(envp);
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