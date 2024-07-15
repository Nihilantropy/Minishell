#include "../include/minishell.h"

static void		create_ex_list(t_shell *shell, t_env **export);
static t_env	*create_ex_node(t_env **export, int len);
static void		check_invalid_name(t_shell *shell, t_env *export);
static void		append_list_to_env(t_shell *shell, t_env *export);

/*
	When export is called by the user we create a list to parse the
	command and the arguments
*/
void	handle_builtin_export(t_shell *shell)
{
	t_env	*export;

	export = NULL;
	create_ex_list(shell, &export);
	if (export->prev == export)
	{
		print_export(shell->env);
		free_env_list(&export);
		return ;
	}
	append_list_to_env(shell, export);
}

/*
	Loop the user string until all the parameter are placed in the list
*/
static void	create_ex_list(t_shell *shell, t_env **export)
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
		current_node = create_ex_node(export, len);
		temp = copy_ex_var(current_node, temp, len);
		current_node->name = copy_ex_name(current_node->var);
		current_node->value = copy_ex_value(current_node->var);
		if (current_node->value)
			current_node->show = true;
	}
	check_invalid_name(shell, *export);
	free(line_copy);
}

/*
	Create the export node with the variable space
	and append to the list
*/
static t_env	*create_ex_node(t_env **export, int len)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		ft_exit_error(ERR_ALLOR_EXPORT);
	new_node->var = malloc(len + 1);
	if (!new_node)
		ft_exit_error(ERR_ALLOC_NEW_NODE);
	new_node->name = NULL;
	new_node->value = NULL;
	new_node->show = false;
	append_env_node(export, new_node);
	return (new_node);
}


/*
	If the name of the argument is invalid, free the current export list
	and display a new prompt
*/
static void	check_invalid_name(t_shell *shell, t_env *export)
{
	int		i;
	t_env	*current_node;

	current_node = export;
	while (current_node)	
	{
		i = 0;
		while (current_node->name[i])
		{
			if (!ft_isalnum(current_node->name[i]) || ft_isdigit(current_node->name[0]))
			{
				rl_replace_line("", 0);
				rl_on_new_line();
				rl_redisplay();
				printf("-bash: export: `%s'", current_node->var);
				printf(": not a valid identifier\n");
				free_env_list(&export);
				shell_prompt(shell);
				return ;
			}
			i++;
		}
		current_node = current_node->next;
	}
}

static void	append_list_to_env(t_shell *shell, t_env *export)
{
	t_env	*export_dup;
	t_env	*current_node;
	t_env	*next_node;

	if (!export)
		return ;
	export_dup = NULL;
	dup_ex_list(export, &export_dup);
	current_node = export_dup;
	print_env_list(export_dup);
	while (current_node)
	{
		next_node = current_node->next;
		append_env_node(&shell->env, current_node);
		current_node = next_node;
	}
	free_env_list(&export);
}
