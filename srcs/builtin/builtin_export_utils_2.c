#include "../../include/minishell.h"

void print_env_list(t_env *env)
{
	t_env	*current_node;

	if (!env)
		return ;
	current_node = env;
	while (current_node)
	{
		printf("\n-------------------\n");
		printf("variable is: %s\n", current_node->var);
		printf("name is: %s\n", current_node->name);
		printf("value is: %s\n", current_node->value);
		printf("show node? %d\n", current_node->show);
		printf("current node pointer is: %p\n", current_node);
		current_node = current_node->next;
	}
}

/*	var length:
		find the length of the entire variable,
		aka the node parameter.
*/
int	var_length(char *line)
{
	int		i;
	char	quote;

	i = 0;
	while (line[i])
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		while (line[i] != ' ' && line[i] != '\t' && line[i])
		{
			if (line[i] == '\"' || line[i] == '\'')
			{
				quote = line[i++];
				while (line[i] != quote && line[i])
					i++;
			}
			i++;
		}
		return (i);
	}
	return (0);
}

/*	copy export variable:
		copy the entire variable in the node and return it.
*/
char	*copy_ex_var(char *str)
{
	char	*var;

	var = ft_strdup(str);
	if (!var)
		ft_exit_error(ERR_ALLOC_VAR);
	return (var);
}

/*	copy export name:
		copy the export node name.
*/
char	*copy_ex_name(char *current_var)
{
	int		i;
	char	*name;

	i = 0;
	while (current_var[i] && current_var[i] != '=')
		i++;
	name = malloc(i + 1);
	if (!name)
		ft_exit_error(ERR_ALLOC_NAME);
	ft_strlcpy(name, current_var, i + 1);
	return (name);
}

/*	copy export value:
		copy the export node value.
*/
char	*copy_ex_value(char *current_var)
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
