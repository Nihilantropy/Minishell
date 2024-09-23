/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:57:08 by mcantell          #+#    #+#             */
/*   Updated: 2024/09/23 13:57:09 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print_env_builtin(t_env *env);

void	handle_builtin_env(t_shell *shell)
{
	print_env_builtin(shell->env);
	g_exit_status = EXIT_STATUS_SUCCESS;
}

/*	print env builtin:
**	print the name and then the value of each node that
**	has the show flag active.
*/
static void	print_env_builtin(t_env *env)
{
	t_env	*current_node;

	current_node = env;
	while (current_node)
	{
		if (!current_node->show)
			current_node = current_node->next;
		else
		{
			printf("%s=%s\n", current_node->name, current_node->value);
			current_node = current_node->next;
		}
	}
}

/*	remove node:
**	This function is not related to the env builtin.
**	It is used in the export and unset builtin.
**	Remove the current node from the env list.
*/
void	remove_node(t_env *current_node, t_env **head)
{
	if (!current_node)
		return ;
	if (!current_node->prev->next)
		*head = current_node->next;
	else if (current_node->prev->next)
		current_node->prev->next = current_node->next;
	if (current_node->next)
		current_node->next->prev = current_node->prev;
	if (current_node->var)
		free(current_node->var);
	if (current_node->name)
		free(current_node->name);
	if (current_node->value)
		free(current_node->value);
	free(current_node);
}