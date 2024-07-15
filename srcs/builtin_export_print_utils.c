#include "../include/minishell.h"

static void	swap_nodes(t_env *current_node, t_env *next_node, t_env **env_dup);

t_env	*sort_nodes(t_env **env_dup)
{
	t_env	*current_node;

	if (!env_dup || !*env_dup)
		return (*env_dup);
	current_node = *env_dup;
	while (current_node && current_node->next)
	{
		if (ft_strcmp(current_node->name, current_node->next->name) > 0)
		{
			printf("current node name is: %s\n", current_node->name);
			printf("next node name is: %s\n", current_node->next->name);
		
			swap_nodes(current_node, current_node->next, env_dup);
			printf("EVVIVA!\n");
			current_node = *env_dup;
			return (*env_dup);
		}
		current_node = current_node->next;
		printf("current node pointer: %p\n", current_node);
		printf("next node pointer: %p\n", current_node->next);
	}
	return (*env_dup);
}

static void	swap_nodes(t_env *current_node, t_env *next_node, t_env **env_dup)
{
	t_env	*prev_node;
	t_env	*next_next_node;
	
	if (!current_node->prev->next)
		*env_dup = next_node;
	prev_node = current_node->prev;
	next_next_node = next_node->next;
	if (prev_node)
		prev_node->next = next_node;
	else
		*env_dup = next_node;
	if (next_next_node)
		next_next_node->prev = current_node;
	current_node->next = next_next_node;
	next_node->prev = prev_node;
	next_node->next = current_node;
	current_node->prev = next_node;
}
