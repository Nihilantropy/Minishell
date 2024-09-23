/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_redir_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:58:10 by mcantell          #+#    #+#             */
/*   Updated: 2024/09/23 13:58:11 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_redir_list	*find_last_redir_node(t_redir_list *redir);

/*	set node type:
**	Set the corrisponding redirection type.
*/
void	set_node_type(t_redir_list *redir, t_arg *current_node)
{
	if (current_node->type.infile)
		redir->type.infile = true;
	else if (current_node->type.outfile)
		redir->type.outfile = true;
	else if (current_node->type.here_doc)
		redir->type.here_doc = true;
	else if (current_node->type.append)
		redir->type.append = true;
	redir->type.is_redir = true;
}

void	append_redir_node(t_redir_list **redir, t_redir_list *new_node)
{
	t_redir_list	*last_node;

	if (!*redir)
	{
		*redir = new_node;
		new_node->prev = new_node;
	}
	else
	{
		last_node = find_last_redir_node(*redir);
		last_node->next = new_node;
		new_node->prev = last_node;
		(*redir)->prev = new_node;
	}
	new_node->next = NULL;
}

static t_redir_list	*find_last_redir_node(t_redir_list *redir)
{
	if (!redir)
		return (NULL);
	while (redir->next)
		redir = redir->next;
	return (redir);
}
