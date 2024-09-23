/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:45:07 by crea              #+#    #+#             */
/*   Updated: 2024/09/23 13:45:08 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	append_node(t_arg **arg, t_arg *new_node)
{
	t_arg	*last_node;

	if (!*arg)
	{
		*arg = new_node;
		new_node->prev = new_node;
	}
	else
	{
		last_node = find_last_arg_node(*arg);
		last_node->next = new_node;
		new_node->prev = last_node;
		(*arg)->prev = new_node;
	}
	new_node->next = NULL;
}

t_arg	*find_last_arg_node(t_arg *arg)
{
	if (!arg)
		return (NULL);
	while (arg->next)
		arg = arg->next;
	return (arg);
}
