#include "../include/minishell.h"

static void	remove_node_from_env(t_env **env, t_env **unset);

void	handle_builtin_unset(t_shell *shell)
{
	t_env	*unset;

	unset = NULL;
	create_unset_list(shell, &unset);
	if (!unset || unset->prev == unset)
		return ;
	remove_node(unset, &unset);
	remove_node_from_env(&shell->env, &unset);
	free_env_list(&unset);
}

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
			if (!ft_strcmp(current_unset_node->name, current_env_node->name))
			{
				remove_node(current_env_node, env);
				print_env_list(*env);
				break ;
			}
			current_env_node = next_env_node;
		}
		next_unset_node = current_unset_node->next;
		remove_node(current_unset_node, unset);
		current_unset_node = next_unset_node;
	}
}

