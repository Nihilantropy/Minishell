#include "../../include/minishell.h"

static void	remove_node_from_env(t_env **env, t_env **unset);

/*	handle builtin unset:
**	create the argument list with the var name to remove from
**	the env list.
*/
void	handle_builtin_unset(t_shell *shell, char **matrix)
{
	t_env	*unset;

	unset = NULL;
	create_unset_list(matrix, &unset);
	if (!unset || unset->prev == unset || shell->pipes_nbr > 0)
	{
		free_env_list(&unset);
		return ;
	}
	remove_node(unset, &unset);
	remove_node_from_env(&shell->env, &unset);
	free_env_list(&unset);
	g_exit_status = EXIT_STATUS_SUCCESS;
}

/*	remove node from env:
**	search the env node to remove from the env list.
**	while doing that we remove the unset node that after
**	each loop.
*/
static void	remove_node_from_env(t_env **env, t_env **unset)
{
	t_env	*current_unset_node;
	t_env	*current_env_node;
	t_env	*next_unset_node;
	t_env	*next_env_node;

	current_unset_node = *unset;
	while (current_unset_node)
	{
		current_env_node = *env;
		while (current_env_node)
		{
			next_env_node = current_env_node->next;
			if (!ft_strcmp(current_unset_node->var, current_env_node->name))
			{
				remove_node(current_env_node, env);
				break ;
			}
			current_env_node = next_env_node;
		}
		next_unset_node = current_unset_node->next;
		remove_node(current_unset_node, unset);
		current_unset_node = next_unset_node;
	}
}

