#include "../../include/minishell.h"

/*	copy variable:
**	copy the entire variable in the
**	'var' field (ex. USER=gino).
*/
char	*copy_var(char *current_var)
{
	char	*var;

	var = ft_strdup(current_var);
	if (!var)
		ft_exit_error(ERR_ENV_VAR);
	return (var);
}

/*	copy name:
**	copy the name part of the variable in
**	the 'name' field (ex. USER).
*/
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

/*	copy value:
**	copy the value part of the variable in
**	the 'value' field (ex. gino).
*/
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

t_env	*find_last_env_node(t_env *env)
{
	if (!env)
		return (NULL);
	while (env->next)
		env = env->next;
	return (env);
}
