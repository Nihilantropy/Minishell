/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:44:12 by crea              #+#    #+#             */
/*   Updated: 2024/09/23 14:53:12 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*	reset redir
**	1) Loop all the redir list. Find each here_doc node to unset the file
**	2) Reset the STDIN and the STDOUT to the default one
**	3) Close the old file descriptor
*/
void	reset_redir(t_shell *shell)
{
	if (dup2(shell->stdin_copy, STDIN_FILENO) == -1)
		perror("dup2 stdin_copy");
	if (dup2(shell->stdout_copy, STDOUT_FILENO) == -1)
		perror("dup2 stdout_copy");
	close(shell->stdin_copy);
	close(shell->stdout_copy);
}

/*	redir input
**	1) Loop all the redir list to find the here_doc nodes
**	2) Loop all the redir list to find the infile nodes
*/
void	redir_input(t_redir_list *redir)
{
	t_redir_list	*current_node;

	current_node = redir;
	while (current_node)
	{
		if (current_node->type.here_doc)
			open_heredoc(current_node);
		else if (current_node->type.infile)
			open_infile(current_node);
		current_node = current_node->next;
	}
}

/*	redir output
**	1) Loop all the redir list to find either the outfile node or the append node
*/
void	redir_output(t_redir_list *redir)
{
	t_redir_list	*current_node;

	current_node = redir;
	while (current_node)
	{
		if (current_node->type.outfile)
			open_outfile(current_node);
		if (current_node->type.append)
			open_append(current_node);
		current_node = current_node->next;
	}
}
