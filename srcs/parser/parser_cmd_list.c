/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:44:44 by crea              #+#    #+#             */
/*   Updated: 2024/09/23 15:21:49 by crea             ###   ########.fr       */
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
