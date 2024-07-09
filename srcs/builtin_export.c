#include "../include/minishell.h"

static void		create_ex_list(t_shell *shell, t_env **export);
static t_env	*create_ex_node(t_env **export, int len);
static int		var_length(char *line);
static char		*copy_var(t_env *current_node, char *temp, int len);

static void print_env_list(t_env *env)
{
	t_env	*current_node;

	if (!env)
		return ;
	current_node = env;
	while (current_node)
	{
		printf("variable is: %s\n", current_node->var);
		//printf("name is: %s\n", current_node->name);
		//printf("value is: %s\n", current_node->value);
		current_node = current_node->next;
	}
}

void	handle_export(t_shell *shell)
{
	t_env	*export;

	export = NULL;
	create_ex_list(shell, &export);
	//create_new_env_node(shell, new_var);
	print_env_list(export);
}

static t_env	*create_ex_node(t_env **export, int len)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		ft_exit_error(ERR_ALLOR_EXPORT);
	new_node->var = malloc(len + 1);
	new_node->name = NULL;
	new_node->value = NULL;
	new_node->show = false;
	append_env_node(export, new_node);
	return (new_node);
}

static int	var_length(char *line)
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

static char	*copy_var(t_env *current_node, char *temp, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		current_node->var[i] = temp[i];
		i++;
	}
	current_node->var[i] = '\0';
	return (temp + len + 1);
}

static void	create_ex_list(t_shell *shell, t_env **export)
{
	char	*temp;
	int		len;
	t_env	*current_node;

	temp = shell->line;
	while (*temp)
	{
		len = var_length(temp);
		current_node = create_ex_node(export, len);
		printf("pointer of node is: %p\n",current_node);
		temp = copy_var(current_node, temp, len);
		printf("temp return value is: %s\n", temp);
	}
}
