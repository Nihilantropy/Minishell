#include "../../include/minishell.h"

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
	current_node->name = copy_ex_name(current_node, current_node->var);
	current_node->value = copy_ex_value(current_node->var);
	if (current_node->value)
		current_node->show = true;
}

int	check_name_arg_error(t_shell *shell, t_env *current_node, t_env **export)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(current_node->name);
	while ((current_node->chain && i < (len - 1)) || (current_node->name[i] && !current_node->chain))
	{
		if (current_node->name[0] != '!' && (ft_isdigit(current_node->name[0]) ||
			(!ft_isalnum(current_node->name[i]))) && current_node->name[i])
		{
			printf("-minishell: export: `%s'", current_node->var);
			printf(": not a valid identifier\n");
			remove_node(current_node, export);
			shell->last_exit_status = EXIT_STATUS_ERROR;
			return (1);
		}
		i++;
	}
	return (0);
}

/*	chain env value:
**	if export += was called, we join the
**	same name node value
*/
void	chain_env_value(t_env **env, t_env *new_node)
{
	t_env	*current_node;
	char	*new_value;
	char	*temp;

	if (!env || !*env || !new_node)
		return ;
	current_node = *env;
	new_value = NULL;
	while (current_node)
	{
		printf("%s\n%s\n", current_node->name, new_node->name);
		if ((current_node->name && new_node->name)
			&& !ft_strcmp(current_node->name, new_node->name))
		{
			new_value = ft_strjoin(current_node->value, new_node->value);
			if (!new_value)
				ft_exit_error(ERR_ENV_CHAIN_VALUE);
			temp = current_node->value;
			current_node->value = new_value;
			free(temp);
		}
		current_node = current_node->next;
	}
}