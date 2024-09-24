/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:45:06 by crea              #+#    #+#             */
/*   Updated: 2024/09/24 13:58:58 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*	handle heredoc:
**	Loop all the command list and all the redirection lists to
**	open the here document in write mode.
*/
void	handle_heredoc(t_shell *shell)
{
	int				status;

	handle_heredoc_process(shell);
	wait(&status);
	g_exit_status = handle_exit_status(status);
}
