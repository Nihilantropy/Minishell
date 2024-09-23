/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:44:34 by crea              #+#    #+#             */
/*   Updated: 2024/09/23 13:44:35 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*	init shell:
**	init the main shell structure.
*/
void	init_shell(t_shell *shell, char **envp)
{
	shell->line = NULL;
	shell->add_to_history = true;
	shell->arg = NULL;
	shell->pipes_nbr = 0;
	shell->env = NULL;
	shell->new_env = NULL;
	init_env(shell, envp);
	shell->path = NULL;
	shell->cmd = NULL;
	shell->error = false;
}
