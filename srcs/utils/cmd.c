/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:45:32 by crea              #+#    #+#             */
/*   Updated: 2024/09/23 15:26:29 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_cmd_list(t_cmd *cmd)
{
	if (!cmd)
		return ;
	while (cmd)
	{
		printf("\n------------------\n");
		print_matrix(cmd->matrix);
		cmd = cmd->next;
	}
}

void	free_cmd_list(t_cmd **cmd)
{
	t_cmd	*current;
	t_cmd	*next_node;

	if (!*cmd)
		return ;
	current = *cmd;
	while (current)
	{
		next_node = current->next;
		if (current->matrix)
			free_matrix(current->matrix);
		free(current);
		current = next_node;
	}
	*cmd = NULL;
}
