/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:44:19 by crea              #+#    #+#             */
/*   Updated: 2024/09/23 13:44:21 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*	ft_getevn:
**	Function to get the corrisponding name value form the
**	env list. Like getenv() function but for the env list.
*/
char	*ft_getenv(t_env *env, char *var_name)
{
	t_env	*current_node;

	current_node = env;
	while (current_node)
	{
		if (!ft_strcmp(current_node->name, var_name))
			return (current_node->value);
		current_node = current_node->next;
	}
	return (NULL);
}
