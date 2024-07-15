#include "../include/minishell.h"

static void	remove_node_from_env(t_env **env, t_env **unset);
static void	remove_node(t_env *current_node, t_env **head);

void	handle_builtin_unset(t_shell *shell)
{
	t_env	*unset;

	unset = NULL;
	create_unset_list(shell, &unset);
	if (unset->prev == unset)
		return ;
	remove_node_from_env(&shell->env, &unset);
	free_env_list(&unset);
}

static void	remove_node_from_env(t_env **env, t_env **unset)
{
	t_env	*current_unset_node;
	t_env	*current_env_node;

	current_env_node = *env;
	while (current_env_node)
	{
		if ((*unset)->next)
			current_unset_node = (*unset)->next;
		else
			break ;
		printf("current unset node pointer is: %p\n", current_unset_node);
		while (current_unset_node)
		{
			printf("unset name {%s} env name: {%s}\n", current_unset_node->name, current_env_node->name);
			if (!ft_strcmp(current_unset_node->name, current_env_node->name))
			{
				remove_node(current_env_node, env);
				remove_node(current_unset_node, unset);
			}
			current_unset_node = current_unset_node->next;
		}
		current_env_node = current_env_node->next;
	}
}

static void	remove_node(t_env *current_node, t_env **head)
{
	if (current_node->prev->next)
		current_node->prev->next = current_node->next;
	else
		*head = current_node->next;
	if (current_node->next)
		current_node->next->prev = current_node->prev;
	if (current_node->var)
		free(current_node->var);
	if (current_node->name)
		free(current_node->name);
	if (current_node->value)
		free(current_node->value);
	free(current_node);
}