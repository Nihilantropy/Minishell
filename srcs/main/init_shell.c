/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:58:00 by mcantell          #+#    #+#             */
/*   Updated: 2024/09/23 13:58:01 by mcantell         ###   ########.fr       */
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
