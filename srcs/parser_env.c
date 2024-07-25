#include "../include/minishell.h"

static int	len_to_token(char *str);
static char	*parse_env_var(t_shell *shell, t_arg *new_node);
static char	*build_env_str(t_arg *new_node, char *var_value, char *end);

/* 
	Function that loops to replace all $VAR
	with the correct variables.
	As we are going to make the current node string, point
	to a different allocated memory string, at the end we free
	our old string.
*/
void	handle_env_var(t_shell *shell, t_arg *new_node)
{
	char	*temp;
	char	*original_temp;

	temp = ft_strdup(new_node->str);
	original_temp = temp;
	printf("temp is: %p\n", temp);
	printf("new node str is %p\n", new_node->str);
	while (*temp)
	{
		if (*(temp + 1) && *temp == '$')
		{
			temp = parse_env_var(shell, new_node);
			if (temp == NULL)
				break ;
		}
		else
			temp++;
	}
	free(original_temp);
}

/* 
	Function to search for the variable name, save it in 
	a string, and use getenv to retrieve its value.
	temp should take the value of the last character + 1 (if any)
	of the main string, taken up to the $, attached to the value
	of the environment variable.
	Handle $? expander status.
*/
static char	*parse_env_var(t_shell *shell, t_arg *new_node)
{
	char		*start;
	char		*end;
	char		var_name[128];
	char		*var_value;

	start = ft_strnstr(new_node->str, "$", ft_strlen(new_node->str));
	end = start + 1;
	if (*end == '?')
	{
		var_value = ft_itoa(shell->last_exit_status);
		end++;
	}
	else
	{
		while ((*end && ft_isalnum(*end)) || *end == '_')
				end++;
		ft_strlcpy(var_name, start + 1, end - start);
		var_value = ft_getenv(shell->env, var_name);
		if (!var_value)
			var_value = "";
	}
	new_node->str = build_env_str(new_node, var_value, end);
	return (end);
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
	char	*old_str;
	char	*new_str;
	char	*first_str;
	char	*second_str;
	int		len;

	old_str = new_node->str;
	len = len_to_token(new_node->str);
	first_str = (char *)malloc(len + 1);
	if (!first_str)
		ft_exit_error(ERR_ALLOC_ENV_STR);
	ft_strlcpy(first_str, new_node->str, len + 1);
	second_str = ft_strjoin(first_str, var_value);
	free(first_str);
	new_str = ft_strjoin(second_str, end);
	free(second_str);
	free(old_str);
	printf("new str is: %s\n", new_str);
	return (new_str);
} // TODO Correct a memory leak

static int	len_to_token(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	return (i);
}
