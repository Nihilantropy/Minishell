#include "../include/minishell.h"

static t_env	*create_unset_node(t_env **unset, int len);
static char		*copy_unset_name(t_env *current_node, char *temp, int len);
static void		parse_unset_str(char *parsed_str, char *str);

void	create_unset_list(t_shell *shell, t_env **unset)
{
	char	*line_copy;
	char	*temp;
	int		len;
	t_env	*current_node;

	line_copy = ft_strdup(shell->line);
	if (!line_copy)
		ft_exit_error(ERR_ALLOC_LINE_COPY);
	temp = line_copy;
	while (*temp)
	{
		len = var_length(temp);
		current_node = create_unset_node(unset, len);
		temp = copy_unset_name(current_node, temp, len);
	}
	free(line_copy);
}

static t_env	*create_unset_node(t_env **unset, int len)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		ft_exit_error(ERR_ALLOR_EXPORT);
	new_node->name = malloc(len + 1);
	if (!new_node->name)
		ft_exit_error(ERR_ALLOC_NAME);
	new_node->var = NULL;
	new_node->value = NULL;
	new_node->show = false;
	append_env_node(unset, new_node);
	return (new_node);
}

static char	*copy_unset_name(t_env *current_node, char *temp, int len)
{
	char	*parsed_name;

	ft_strlcpy(current_node->name, temp, (len + 1));
	parsed_name = ft_strtrim(current_node->name, " \t\v\r");
	parse_unset_str(current_node->name, parsed_name);
	return (temp + len);
}

static void	parse_unset_str(char *parsed_str, char *str)
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
}
