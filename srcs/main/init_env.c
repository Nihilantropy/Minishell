/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:44:31 by crea              #+#    #+#             */
/*   Updated: 2024/09/23 15:04:25 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	del_same_name_node(t_env **env, t_env *new_node);
static void	handle_node_pointer(t_env *current_node, t_env *new_node);

/*	init env:
**	create a list copy of the envp (variable enviroment) at opening.
*/
void	init_env(t_shell *shell, char **envp)
{
	char	**current_var;

	current_var = envp;
	while (*current_var)
	{
		create_new_env_node(shell, *current_var);
		current_var++;
	}
	update_shell_env_level(shell);
	update_new_shell_env(shell);
}

/*	crete new env node:
**	Create the env node with 3 string:
**	1) the entire variable
**	2) the name of the variable
**	3) the value of the variable
*/
void	create_new_env_node(t_shell *shell, char *current_var)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		ft_exit_error(ERR_ALLOC_ENV);
	new_node->var = copy_var(current_var);
	new_node->name = copy_name(current_var);
	new_node->value = copy_value(current_var);
	new_node->chain = false;
	new_node->show = true;
	append_env_node(&shell->env, new_node);
}

void	append_env_node(t_env **env, t_env *new_node)
{
	t_env	*last_node;

	if (!*env)
	{
		*env = new_node;
		new_node->prev = new_node;
	}
	else if (del_same_name_node(env, new_node))
		return ;
	else
	{
		last_node = find_last_env_node(*env);
		last_node->next = new_node;
		new_node->prev = last_node;
		(*env)->prev = new_node;
	}
	new_node->next = NULL;
}

/*	delete same name node:
**	if the name node that we are appending is already in the list,
**	we replace the old node with the new one.
*/
static int	del_same_name_node(t_env **env, t_env *new_node)
{
	t_env	*current_node;

	if (!env || !*env || !new_node)
		return (0);
	current_node = *env;
	while (current_node)
	{
		if ((current_node->name && new_node->name)
			&& !ft_strcmp(current_node->name, new_node->name))
		{
			if (new_node->chain)
				chain_env_value(current_node, new_node);
			if (current_node == *env)
				*env = new_node;
			handle_node_pointer(current_node, new_node);
			free_current_node(current_node);
			return (1);
		}
		current_node = current_node->next;
	}
	return (0);
}

/*	handle node pinter:
**	ensure that the node swapping is done correctly,
**	handling all the necessary pointers.
*/
static void	handle_node_pointer(t_env *current_node, t_env *new_node)
{
	if (current_node->prev->next)
		current_node->prev->next = new_node;
	if (current_node->next)
		current_node->next->prev = new_node;
	new_node->next = current_node->next;
	new_node->prev = current_node->prev;
}
