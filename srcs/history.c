/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:03:54 by crea              #+#    #+#             */
/*   Updated: 2024/06/08 17:03:54 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_history(t_shell *shell)
{
	search_here_doc(shell);
	if (shell->add_to_history)
		add_history(shell->line);
	shell->add_to_history = true;
}

void	search_here_doc(t_shell *shell)
{
	if (!shell->arg)
		return ;
	while (shell->arg)
	{
		if (shell->arg->token.t_here_doc)
			shell->add_to_history = false;
		shell->arg = shell->arg->next;
	}
}