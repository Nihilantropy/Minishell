#include "../../include/minishell.h"

static char	*build_env_str(t_arg *new_node, char *var_value, char *end);
static int	len_to_token(char *str);

/*
	Expand the last exit status to a string
*/
char	*handle_exit_status_var(t_shell *shell, t_arg *new_node, char *end)
{
	char	*var_value;
	char	*new_str;

	var_value = ft_itoa(shell->last_exit_status);
	new_str = build_env_str(new_node, var_value, end);
	free(var_value);
	return (new_str);
}

/*
	Expand the env var ($ARG) to a string
*/
char	*hanlde_env_var(t_shell *shell, t_arg *new_node, char *start, char *end)
{
	char	var_name[1024];
	char	*var_value;
	char	*new_str;

	while ((*end && ft_isalnum(*end)) || *end == '_')
				end++;
	ft_strlcpy(var_name, start + 1, end - start);
	var_value = ft_getenv(shell->env, var_name);
	if (!var_value)
		var_value = "";
	new_str = build_env_str(new_node, var_value, end);
	return (new_str);
}

/*
	Function to split the main string into 2 parts:
	the first part goes up to the $
	the second part takes the first part and appends the environment variable
	Then we join the new string with the modified VAR (var_value)
	and make our current node string point to the new string.
*/
static char	*build_env_str(t_arg *new_node, char *var_value, char *end)
{
	char	*new_str;
	char	*first_str;
	char	*second_str;
	int		len;

	len = len_to_token(new_node->str);
	first_str = (char *)malloc(len + 1);
	if (!first_str)
		ft_exit_error(ERR_ALLOC_ENV_STR);
	ft_strlcpy(first_str, new_node->str, len + 1);
	second_str = ft_strjoin(first_str, var_value);
	free(first_str);
	new_str = ft_strjoin(second_str, end);
	free(second_str);
	printf("new_node->str is: %s\n", new_node->str);
	return (new_str);
}

static int	len_to_token(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	return (i);
}
