/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:45:15 by crea              #+#    #+#             */
/*   Updated: 2024/09/23 13:45:16 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	init_redir(t_arg *new_node);
static void	init_token(t_arg *new_node);

/*	init new node:
**	Initializing the new node to have all known values.
*/
t_arg	*init_new_node(void)
{
	t_arg	*new_node;

	new_node = (t_arg *)malloc(sizeof(t_arg));
	if (!new_node)
		ft_exit_error(ERR_ALLOC_NEW_NODE);
	new_node->index = 0;
	new_node->str = NULL;
	init_token(new_node);
	init_redir(new_node);
	new_node->quote.double_q = false;
	new_node->quote.single_q = false;
	new_node->quote.none_q = false;
	new_node->chained = false;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

static void	init_token(t_arg *new_node)
{
	new_node->token.is_token = false;
	new_node->token.pipe = false;
	new_node->token.t_infile = false;
	new_node->token.t_outfile = false;
	new_node->token.t_here_doc = false;
	new_node->token.t_append = false;
}

static void	init_redir(t_arg *new_node)
{
	new_node->type.is_redir = false;
	new_node->type.infile = false;
	new_node->type.outfile = false;
	new_node->type.here_doc = false;
	new_node->type.append = false;
}

/*	find total path:
**	Find the PATH for the executable
*/
void	find_total_path(t_shell *shell)
{
	t_env	*current_node;

	current_node = shell->env;
	while (current_node)
	{
		if (!ft_strcmp(current_node->name, "PATH"))
			break ;
		current_node = current_node->next;
	}
	if (!current_node)
		return ;
	shell->path = ft_split(current_node->value, ':');
}
