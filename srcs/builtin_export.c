#include "../include/minishell.h"

static void		create_ex_list(t_shell *shell, t_env **export);
static t_env	*create_ex_node(t_env **export, int len);

/*
	When export is called by the user we create a list to parse the
	command and the arguments
*/
void	handle_export(t_shell *shell)
{
	t_env	*export;

	export = NULL;
	create_ex_list(shell, &export);
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
	new_node->name = NULL;
	new_node->value = NULL;
	new_node->show = false;
	append_env_node(export, new_node);
	return (new_node);
}

/*
	Loop the user string until all the parameter are placed in the list
*/
static void	create_ex_list(t_shell *shell, t_env **export)
{
	char	*temp;
	int		len;
	t_env	*current_node;
	int		i = 0;
	temp = shell->line;
	while (*temp)
	{
		i++;
		len = var_length(temp);
		current_node = create_ex_node(export, len);
		temp = copy_ex_var(current_node, temp, len);
		current_node->name = copy_ex_name(current_node->var);
		current_node->value = copy_ex_value(current_node->var);
	}
	print_env_list(*export);
	free_env_list(export);
}
