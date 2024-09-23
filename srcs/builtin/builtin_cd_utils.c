/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:43:20 by crea              #+#    #+#             */
/*   Updated: 2024/09/23 13:43:21 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_oldpwd_node(t_env *current_node, char *current_pwd)
{
	char	*current_pwd_dup;

	current_pwd_dup = ft_strdup(current_pwd);
	if (current_node->value)
		free(current_node->value);
	current_node->value = current_pwd_dup;
}

void	update_pwd_node(t_env *current_node, char *new_pwd)
{
	char	*new_pwd_dup;

	new_pwd_dup = ft_strdup(new_pwd);
	if (current_node->value)
		free(current_node->value);
	current_node->value = new_pwd_dup;
}
