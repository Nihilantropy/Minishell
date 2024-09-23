/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:44:29 by crea              #+#    #+#             */
/*   Updated: 2024/09/23 13:44:30 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	create_new_shell_level_node(t_shell *shell, char *new_level);
static int	env_list_length(t_env *env);

/*	update shell env level:
**	finding the shell level (SHLVL) env var and incrising 
**	the level of the shell by 1.
*/
void	update_shell_env_level(t_shell *shell)
{
	t_env	*current_node;
	int		old_level;
	char	*new_level;

	old_level = 0;
	current_node = shell->env;
	while (current_node)
	{
		if (!ft_strcmp(current_node->name, "SHLVL"))
		{
			if (current_node->value)
				old_level = ft_atoi(current_node->value);
			break ;
		}
		current_node = current_node->next;
	}
	old_level++;
	new_level = ft_itoa(old_level);
	create_new_shell_level_node(shell, new_level);
	free(new_level);
}

static void	create_new_shell_level_node(t_shell *shell, char *new_level)
{
	char	*var;

	var = ft_strjoin("SHLVL=", new_level);
	create_new_env_node(shell, var);
	free(var);
}

/*	update new shell env:
**	create a matrix copy of the modified env
**	before passing it to a command.
**	This way we ensure that (for exmpl.), if the
**	user open a subsshell writing ./minishell,
**	the variable enviroment is passed to the new
**	shell correctly, otherwise it would be opened with
**	the old envp.
*/
void	update_new_shell_env(t_shell *shell)
{
	int		y;
	int		len;
	t_env	*current_node;

	if (shell->new_env)
		free_matrix(shell->new_env);
	y = 0;
	current_node = shell->env;
	len = env_list_length(shell->env);
	shell->new_env = malloc(sizeof(char *) * (len + 1));
	if (!shell->new_env)
		ft_exit_error(ERR_NEW_ENV_ALLOC);
	while (current_node)
	{
		shell->new_env[y] = ft_strdup(current_node->var);
		y++;
		current_node = current_node->next;
	}
	shell->new_env[y] = NULL;
}

static int	env_list_length(t_env *env)
{
	int		len;
	t_env	*current_node;

	len = 0;
	current_node = env;
	while (current_node)
	{
		current_node = current_node->next;
		len++;
	}
	return (len);
}
