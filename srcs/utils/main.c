/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:45:35 by crea              #+#    #+#             */
/*   Updated: 2024/09/23 13:45:36 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*	free prompt:
**	free all the memory of the read line and
**	the lists of the parsed line. 
**	Free also the path, so it will reset everytime
**	the user insert a prompt.
*/
void	free_prompt(t_shell *shell)
{
	if (shell->line && shell->line[0] == '\0')
	{
		free(shell->line);
		shell->line = NULL;
		return ;
	}
	free_all_redir_list(shell->cmd);
	free_cmd_list(&shell->cmd);
	free_list(&shell->arg);
	free_matrix(shell->path);
	shell->path = NULL;
}

/*	free shell:
**	at exit, free the duplicated env list
**	and the relative env matrix
*/
void	free_shell(t_shell *shell)
{
	if (shell->env)
		free_env_list(&shell->env);
	if (shell->new_env[0])
		free_matrix(shell->new_env);
}