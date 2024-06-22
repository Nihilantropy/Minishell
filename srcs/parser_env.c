#include "../include/minishell.h"

static int	len_to_token(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	return (i - 1);
}

/* Function to split the main string into 3 parts:
   the first part goes up to the $
   the second part takes the first part and appends the environment variable
   the third part takes the value of the first string, removing the first 
   occurrence of $VAR, so it can be appended to the second string.
   Once the new string is put back together, we make the node's string 
   point to this new string. */
static char	*build_env_str(char *str, char *var_value, char *end)
{
	char	*first_str;
	char	*second_str;
	char	*third_str;
	int		len;

	len = len_to_token(str);
	first_str = (char *)malloc(len + 1);
	if (!first_str)
		ft_exit_error("ERR FIRST STR MALLOC\n");
	ft_strlcpy(first_str, str, len + 1);
	second_str = ft_strjoin(first_str, var_value);
	if (*end + 1)
	{
		len = ft_strlen(end + 1);
		third_str = (char *)malloc(len + 1);
		if (!third_str)
			ft_exit_error("ERR THIRD STR MALLOC\n");
		ft_strlcpy(third_str, end + 1, len + 1);
		str = ft_strjoin(second_str, third_str);
	}
	return (second_str);
}


/* Function to search for the variable name, save it in 
   a string, and use getenv to retrieve its value.
   temp should take the value of the last character + 1 (if any)
   of the main string, taken up to the $, attached to the value
   of the environment variable.
   If there is an input like $$$$, the program will still see
   $$ and then see the rest */
static char	*parse_env_var(char *str)
{
	char		*start;
	char		*end;
	char		var_name[128];
	char		*var_value;
	char		*temp;

	start = ft_strnstr(str, "$", ft_strlen(str));
	end = start + 1;
	if (!*end || ft_isdigit(*end))
		return (NULL);
	while (start)
	{
		if (*end + 1 == '$')
		{
			end++;
			break ;
		}
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
	temp = build_env_str(str, var_value, end);
	return (temp);
}

/* Function that loops to replace all $VAR
   with the correct variables */
void	handle_env_var(t_arg *new_node)
{
	char	*temp;

	temp = new_node->str;
	while (*temp)
	{
		if (*temp == '$')
		{
			temp = parse_env_var(new_node->str);
			if (temp == NULL)
				break ;
		}
		temp++;
	}
}

// TODO .... NON va un cazzo :)