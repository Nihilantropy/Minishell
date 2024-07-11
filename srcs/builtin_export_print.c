#include "../include/minishell.h"

static void	dup_env_list(t_env *env, t_env **env_dup);
static void	create_dup_env_node(t_env *current_env_node, t_env **env_dup);
//static void	swap_nodes(t_env *current_node, t_env *next_node, t_env **env_dup);
//static void	sort_nodes(t_env **env_dup);

void	print_export(t_env *env)
{
	t_env	*env_dup;
	t_env	*current_node;
	if (!env)
		return ;
	print_env_list(env);
	dup_env_list(env, &env_dup);
	print_env_list(env_dup);


	//sort_nodes(&env_dup);
	current_node = env_dup;
	while (current_node)
	{
		printf("declare -x %s=", current_node->name);
		if (current_node->value)
			printf("\"%s\"", current_node->value);
		ft_putnl();
		current_node = current_node->next;
	}
	free_env_list(&env_dup);
}

static void	dup_env_list(t_env *env, t_env **env_dup)
{
	t_env	*current_env_node;

	current_env_node = env;
	while (current_env_node)
	{
		create_dup_env_node(current_env_node, env_dup);
		current_env_node = current_env_node->next;
	}
}

static void	create_dup_env_node(t_env *current_env_node, t_env **env_dup)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		ft_exit_error(ERR_ALLOC_NEW_NODE);
	new_node->var = ft_strdup(current_env_node->var);
	new_node->name = ft_strdup(current_env_node->name);
	if (current_env_node->value)
		new_node->value = ft_strdup(current_env_node->value);
	new_node->show = current_env_node->show;
	append_env_node(env_dup, new_node);
}
/*
static void	swap_nodes(t_env *current_node, t_env *next_node, t_env **env_dup)
{
	if (!current_node->prev->next)
		*env_dup = next_node;
	current_node->next = next_node->next;
	next_node->prev = current_node->prev;
	next_node->next = current_node;
	current_node->prev = next_node;
}

static void	sort_nodes(t_env **env_dup)
{
	t_env	*current_node;

	current_node = *env_dup;
	while (current_node && current_node->next)
	{
		if (current_node->name[0] > current_node->next->name[0])
		{
			swap_nodes(current_node, current_node->next, env_dup);
			current_node = *env_dup;
		}
		current_node = current_node->next;
	}
}

*/