/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:58:08 by mcantell          #+#    #+#             */
/*   Updated: 2024/09/23 13:58:09 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_cmd		*find_last_cmd_node(t_cmd *cmd);

void	append_cmd_node(t_cmd **cmd, t_cmd *new_node)
{
	t_cmd	*last_node;

	if (!*cmd)
	{
		*cmd = new_node;
		new_node->prev = new_node;
	}
	else
	{
		last_node = find_last_cmd_node(*cmd);
		last_node->next = new_node;
		new_node->prev = last_node;
		(*cmd)->prev = new_node;
	}
	new_node->next = NULL;
}

static t_cmd	*find_last_cmd_node(t_cmd *cmd)
{
	if (!cmd)
		return (NULL);
	while (cmd->next)
		cmd = cmd->next;
	return (cmd);
}

