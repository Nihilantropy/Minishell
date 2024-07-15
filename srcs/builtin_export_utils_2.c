#include "../include/minishell.h"

static char	*parse_ex_str(char *parsed_value, char *value);

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

/*
	Find the length of the entire variable,
	aka the node parameter
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

/*
	Copy the entire variable in the node and return
	a pointer to the end of the variable + 1
*/
char	*copy_ex_var(t_env *current_node, char *temp, int len)
{
	int		i;
	char	*parsed_var;
	char	*temp_var;

	i = 0;
	while (i < len)
	{
		current_node->var[i] = temp[i];
		i++;
	}
	current_node->var[i] = '\0';
	parsed_var = malloc(ft_strlen(current_node->var) + 1);
	if (!parsed_var)
		ft_exit_error(ERR_ALLOC_PARSED_VAR);
	i = 0;
	while (current_node->var[i] == ' ' || current_node->var[i] == '\t')
		i++;
	ft_strlcpy(parsed_var, (current_node->var + i), (ft_strlen(current_node->var) + 1));
	temp_var = current_node->var;
	current_node->var = parsed_var;
	free(temp_var);
	return (temp + len);
}

/*
	Copy the export node value, parsing the quote correctly
*/
char	*copy_ex_value(char *current_var)
{
	char	*value;
	char	*parsed_value;
	char	*start;

	value = NULL;
	start = ft_strchr(current_var, '=');
	if (!start)
		return (NULL);
	if ((*start + 1) == '\0')
		return ("");
	value = ft_strdup(start + 1);
	parsed_value = malloc(ft_strlen(value) + 1);
	if (!value || !parsed_value)
		ft_exit_error(ERR_ALLOC_VALUE);
	parse_ex_str(parsed_value, value);
	return (parsed_value);
}

/*
	Copy the export node name, parsing the quote correctly
*/
char	*copy_ex_name(char *current_var)
{
	int		i;
	char	*name;
	char	*parsed_name;

	i = 0;
	while (current_var[i] && current_var[i] != '=')
		i++;
	name = malloc(i + 1);
	parsed_name = malloc(i + 1);
	if (!name || !parsed_name)
		ft_exit_error(ERR_ALLOC_NAME);
	ft_strlcpy(name, current_var, i + 1);
	parse_ex_str(parsed_name, name);
	return (parsed_name);
}

/*
	Remove the quote from correct quote from the string,
	then free the old string
*/
static char	*parse_ex_str(char *parsed_str, char *str)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i++];
			while (str[i] != quote && str[i])
				parsed_str[j++] = str[i++];
			if (str[i] == quote)
				i++;
		}
		else
			parsed_str[j++] = str[i++];
	}
	parsed_str[j] = '\0';
	free(str);
	return (parsed_str);
}

