/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:45:34 by crea              #+#    #+#             */
/*   Updated: 2024/09/23 15:25:56 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_env_list(t_env *env)
{
	t_env	*current_node;

	if (!env)
		return ;
	current_node = env;
	while (current_node)
	{
		printf("\n-------------------\n");
		printf("variable is: %s\n", current_node->var);
		printf("name is: %s\n", current_node->name);
		printf("value is: %s\n", current_node->value);
		printf("show node? %d\n", current_node->show);
		printf("current node pointer is: %p\n", current_node);
		current_node = current_node->next;
	}
}

void	free_env_list(t_env **env)
{
	t_env	*current;
	t_env	*next_node;

	if (!*env)
		return ;
	current = *env;
	while (current)
	{
		next_node = current->next;
		if (current->var)
			free(current->var);
		if (current->name)
			free(current->name);
		if (current->value)
			free(current->value);
		free(current);
		current = next_node;
	}
	*env = NULL;
}
