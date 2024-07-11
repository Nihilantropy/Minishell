#include "../include/minishell.h"

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
	append_env_node(export_dup, new_node);
}
