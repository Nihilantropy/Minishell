/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:43:57 by crea              #+#    #+#             */
/*   Updated: 2024/09/23 13:43:58 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_env	*create_unset_node(t_env **unset);

void	create_unset_list(char **matrix, t_env **unset)
{
	char	**matrix_copy;
	int		y;
	t_env	*current_node;

	matrix_copy = dup_matrix(matrix);
	if (!matrix_copy)
		ft_exit_error(ERR_ALLOC_MATRIX_COPY);
	y = 0;
	while (matrix_copy[y])
	{
		current_node = create_unset_node(unset);
		current_node->var = copy_ex_var(matrix[y]);
		y++;
	}
	free_matrix(matrix_copy);
}

static t_env	*create_unset_node(t_env **unset)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		ft_exit_error(ERR_ALLOR_EXPORT);
	new_node->var = NULL;
	new_node->name = NULL;
	new_node->value = NULL;
	new_node->show = false;
	append_env_node(unset, new_node);
	return (new_node);
}
