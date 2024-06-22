#include "../include/minishell.h"
/*
static void	build_env_str(char *str, char *var_value)
{
	char	*new
}*/

static int	parse_env_var(char *str)
{
	char		*start;
	char		*end;
	char		var_name[128];
	char		*var_value;

	start = ft_strnstr(str, "$", ft_strlen(str));
	end = start + 1;
	if (!*end || ft_isdigit(*end))
		return (0);
	while (start)
	{
		while ((*end && ft_isalnum(*end)) || *end == '_')
			end++;
	}
	ft_strlcpy(var_name, start + 1, end - start);
	var_name[end - start] = '\0';
	printf("var name is %s\n", var_name);
	var_value = getenv(var_name);
	if (!var_value)
		var_value = "";
	printf("var value is %s\n", var_value);
	// build_env_str(str, var_value); TODO
	// FUNCTION DOESN'T WORK
	// check infinite loop
	return (1);
}

void	handle_env_var(t_arg *new_node)
{
	while (ft_strchr(new_node->str, '$'))
	{
		if (!parse_env_var(new_node->str))
			break ;
		break ; // REMOVE
	}
}