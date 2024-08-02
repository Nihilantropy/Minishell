#include "../../include/minishell.h"

static char	*parse_env_var(t_shell *shell, t_arg *new_node);
char		*handle_exit_status_var(t_shell *shell, t_arg *new_node, char *end);
char		*hanlde_env_var(t_shell *shell, t_arg *new_node, char *start, char *end);

/* 
	Function that loops to replace all $VAR
	with the correct variables.
	If the string is parsed, return to the start of the string
	and restart the loop until all '$' are correctly parsed
*/

void	handle_env_var(t_shell *shell, t_arg *new_node)
{
	int		i;
	char	*old_str;
	char	*new_str;

	i = 0;
	while (new_node->str[i])
	{
		if (new_node->str[i + 1] && new_node->str[i] == '$')
		{
			old_str = new_node->str;
			new_str = parse_env_var(shell, new_node);
			if (!new_str)
				break ;
			new_node->str = new_str;
			free(old_str);
			i = 0;
		}
		else
			i++;
	}
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
	char		*new_str;

	start = ft_strnstr(new_node->str, "$", ft_strlen(new_node->str));
	end = start + 1;
	if (!*end)
		return (NULL);
	if (*end == '?')
	{
		end++;
		new_str = handle_exit_status_var(shell, new_node, end);
	}
	else
		new_str = hanlde_env_var(shell, new_node, start, end);
	return (new_str);
}
