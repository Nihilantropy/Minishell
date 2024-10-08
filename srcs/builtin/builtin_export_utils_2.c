/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:43:50 by crea              #+#    #+#             */
/*   Updated: 2024/09/24 12:58:46 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*	var length:
**	find the length of the entire variable,
**	aka the node parameter.
*/
int	var_length(char *line)
{
	int		i;
	char	quote;

	i = 0;
	while (line[i])
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		while (line[i] != ' ' && line[i] != '\t' && line[i])
		{
			if (line[i] == '\"' || line[i] == '\'')
			{
				quote = line[i++];
				while (line[i] != quote && line[i])
					i++;
			}
			i++;
		}
		return (i);
	}
	return (0);
}

/*	copy export variable:
**	copy the entire variable in the node and return it.
*/
char	*copy_ex_var(char *str)
{
	char	*var;

	var = ft_strdup(str);
	if (!var)
		ft_exit_error(ERR_ALLOC_VAR);
	return (var);
}

/*	copy export name:
**	copy the export node name.
*/
char	*copy_ex_name(t_env *current_node, char *current_var)
{
	int		i;
	char	*name;

	i = 0;
	while (current_var[i] && current_var[i] != '=')
		i++;
	if (ft_strncmp(current_var, "=", 1) == 0)
		return (NULL);
	name = malloc(i + 1);
	if (!name)
		ft_exit_error(ERR_ALLOC_NAME);
	if (current_var[i] == '=' && current_var[i - 1] == '+')
		current_node->chain = true;
	if (current_node->chain)
		ft_strlcpy(name, current_var, i);
	else
		ft_strlcpy(name, current_var, i + 1);
	return (name);
}

/*	copy export value:
**	copy the export node value.
*/
char	*copy_ex_value(char *current_var)
{
	char	*value;
	char	*start;

	value = NULL;
	start = ft_strchr(current_var, '=');
	if (!start)
		return (NULL);
	if ((*start + 1) == '\0')
		return ("");
	value = ft_strdup(start + 1);
	if (!value)
		ft_exit_error(ERR_ALLOC_VALUE);
	return (value);
}
