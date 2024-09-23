/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_print_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:43:37 by crea              #+#    #+#             */
/*   Updated: 2024/09/23 13:43:37 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	swap_nodes(t_env *current_node, t_env *next_node);

/*	sort nodes:
**	sort in ascending order.
*/
void	sort_nodes(t_env **env_dup)
{
	t_env	*current_node;

	if (!env_dup || !*env_dup)
		return ;
	current_node = *env_dup;
	while (current_node && current_node->next)
	{
		if (ft_strcmp(current_node->name, current_node->next->name) > 0)
		{
			swap_nodes(current_node, current_node->next);
			current_node = *env_dup;
		}
		else
			current_node = current_node->next;
	}
}

/*	swap nodes:
**	swap the content of the nodes.
*/
static void	swap_nodes(t_env *current_node, t_env *next_node)
{
	char	*temp_var;
	char	*temp_name;
	char	*temp_value;
	t_bool	temp_show;

	temp_var = current_node->var;
	temp_name = current_node->name;
	temp_value = current_node->value;
	temp_show = current_node->show;
	current_node->var = next_node->var;
	current_node->name = next_node->name;
	current_node->value = next_node->value;
	current_node->show = next_node->show;
	next_node->var = temp_var;
	next_node->name = temp_name;
	next_node->value = temp_value;
	next_node->show = temp_show;
}
