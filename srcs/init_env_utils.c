#include "../include/minishell.h"

char	*copy_var(char *current_var)
{
	char	*var;

	var = ft_strdup(current_var);
	if (!var)
		ft_exit_error("var does not exist\n");
	return (var);
}

char	*copy_name(char *current_var)
{
	int		i;
	char	*name;

	i = 0;
	while (current_var[i] && current_var[i] != '=')
		i++;
	name = malloc(i + 1);
	if (!name)
		ft_exit_error(ERR_ALLOC_NAME);
	i = 0;
	while (current_var[i] && current_var[i] != '=')
	{
		name[i] = current_var[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

char	*copy_value(char *current_var)
{
	char	*value;
	char	*start;

	value = NULL;
	start = ft_strchr(current_var, '=');
	if (!start)
		return (NULL);
	if ((*start + 1) == '\0')
		return ("");
	value = ft_strdup(start + 1);
	if (!value)
		ft_exit_error(ERR_ALLOC_VALUE);
	return (value);
}

void	free_env_list(t_env **env)
{
	t_env	*current;
	t_env	*next_node;

	if (!*env)
		return ;
	current = *env;
	while (current)
	{
		next_node = current->next;
		free(current->var);
		free(current->name);
		free(current->value);
		free(current);
		current = next_node;
	}
	*env = NULL;
}