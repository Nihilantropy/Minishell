#include "../include/minishell.h"

char	*ft_getenv(t_env *env, char *var_name)
{
	t_env	*current_node;

	current_node = env;
	while (current_node)
	{
		if (!ft_strcmp(current_node->name, var_name))
			return (current_node->value);
		current_node = current_node->next;
	}
	return (NULL);
}