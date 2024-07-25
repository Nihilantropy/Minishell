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

void	copy_ex_node(t_env *current_node, char **matrix, int y)
{
	current_node->var = copy_ex_var(matrix[y]);
	current_node->name = copy_ex_name(current_node->var);
	current_node->value = copy_ex_value(current_node->var);
	if (current_node->value)
		current_node->show = true;
}

int	check_name_arg_error(t_shell *shell, t_env *current_node, t_env **export)
{
	int	i;

	i = 0;
	while (current_node->name[i++])
	{
		if (current_node->name[0] != '!' && (ft_isdigit(current_node->name[0]) ||
			(!ft_isalnum(current_node->name[i]))) && current_node->name[i])
		{
			printf("-bash: export: `%s'", current_node->var);
			printf(": not a valid identifier\n");
			remove_node(current_node, export);
			shell->last_exit_status = EXIT_STATUS_ERROR;
			return (1);
		}
		else if (current_node->name[0] == '!')
		{
			printf("-bash: %s: event not found\n", current_node->var);
			remove_node(current_node, export);
			shell->last_exit_status = EXIT_STATUS_SUCCESS;
			return (1);
		}
	}
	return (0);
}