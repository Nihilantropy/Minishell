/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:43:47 by crea              #+#    #+#             */
/*   Updated: 2024/09/23 17:03:23 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	create_dup_ex_node(t_env *current_ex_node, t_env **export_dup);

void	dup_ex_list(t_env *export, t_env **export_dup)
{
	t_env	*current_ex_node;

	current_ex_node = export->next;
	while (current_ex_node)
	{
		create_dup_ex_node(current_ex_node, export_dup);
		current_ex_node = current_ex_node->next;
	}
}

static void	create_dup_ex_node(t_env *current_ex_node, t_env **export_dup)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		ft_exit_error(ERR_ALLOC_NEW_NODE);
	new_node->var = ft_strdup(current_ex_node->var);
	new_node->name = ft_strdup(current_ex_node->name);
	new_node->value = ft_strdup(current_ex_node->value);
	new_node->show = current_ex_node->show;
	new_node->chain = current_ex_node->chain;
	append_env_node(export_dup, new_node);
}

void	copy_ex_node(t_env *current_node, char **matrix, int y)
{
	current_node->var = copy_ex_var(matrix[y]);
	current_node->name = copy_ex_name(current_node, current_node->var);
	current_node->value = copy_ex_value(current_node->var);
	if (current_node->value)
		current_node->show = true;
}

int	check_name_arg_error(t_env *current_node, t_env **export)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(current_node->name);
	while ((current_node->chain && i < (len - 1))
		|| (current_node->name[i] && !current_node->chain))
	{
		if (current_node->name[0] != '!'
			&& (ft_isdigit(current_node->name[0])
				|| (!ft_isalnum(current_node->name[i])))
			&& current_node->name[i])
		{
			ft_putstr_fd("-minishell: export: `", 2);
			ft_putstr_fd(current_node->var, 2);
			ft_putstr_fd("'", 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			remove_node(current_node, export);
			g_exit_status = EXIT_STATUS_ERROR;
			return (1);
		}
		i++;
	}
	return (0);
}

/*	chain env value:
**	if export += was called, we join the
**	same name node value
*/
void	chain_env_value(t_env *current_node, t_env *new_node)
{
	char	*new_value;
	char	*temp;

	if ((current_node->name && new_node->name)
		&& !ft_strcmp(current_node->name, new_node->name))
	{
		new_value = ft_strjoin(current_node->value, new_node->value);
		if (!new_value)
			ft_exit_error(ERR_ENV_CHAIN_VALUE);
		temp = new_node->value;
		new_node->value = new_value;
		free(temp);
	}
}
