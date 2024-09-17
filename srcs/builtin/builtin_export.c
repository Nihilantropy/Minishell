#include "../../include/minishell.h"

static void		create_ex_list(char **matrix, t_env **export);
static t_env	*create_ex_node(t_env **export);
static int		check_invalid_name(t_env **export);
static void		append_list_to_env(t_shell *shell, t_env *export);
void			copy_ex_node(t_env *current_node, char **matrix, int y);
int				check_name_arg_error(t_env *current_node, t_env **export);

/*	handle builtin export:
**	when export is called by the user we create a list to parse the
**	command and the arguments.
*/
void	handle_builtin_export(t_shell *shell, char **matrix)
{
	t_env	*export;

	export = NULL;
	create_ex_list(matrix, &export);
	if (export->prev == export)
	{
		print_export(shell->env);
		free_env_list(&export);
		return ;
	}
	append_list_to_env(shell, export);
	update_new_shell_env(shell);
	g_exit_status = EXIT_STATUS_SUCCESS;
}

/*	create export list:
**	loop the cmd matrix until all the parameter are placed in the list.
*/
static void	create_ex_list(char **matrix, t_env **export)
{
	char	**matrix_copy;
	int		y;
	t_env	*current_node;

	matrix_copy = dup_matrix(matrix);
	if (!matrix_copy)
		ft_exit_error(ERR_ALLOC_LINE_COPY);
	y = 0;
	while (matrix_copy[y])
	{
		current_node = create_ex_node(export);
		copy_ex_node(current_node, matrix, y);
		y++;
	}
	if (check_invalid_name(export) == 1)
	{
		free_matrix(matrix_copy);
		return ;
	}
	free_matrix(matrix_copy);
	g_exit_status = EXIT_STATUS_SUCCESS;
}

/*	create export node:
**	create the export node with the variable space
**	and append to the list.
*/
static t_env	*create_ex_node(t_env **export)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		ft_exit_error(ERR_ALLOR_EXPORT);
	new_node->var = NULL;
	new_node->name = NULL;
	new_node->value = NULL;
	new_node->show = false;
	new_node->chain = false;
	append_env_node(export, new_node);
	return (new_node);
}


/*	check invalid name:
**	if the name of the argument is invalid, free the current export list
**	and display a new prompt.
*/
static int	check_invalid_name(t_env **export)
{
	int		i;
	t_env	*current_node;

	current_node = (*export)->next;
	while (current_node)	
	{
		i = 0;
		while (current_node->name[i])
		{
			if (check_name_arg_error(current_node, export) == 1)
				return (1);
			i++;
		}
		current_node = current_node->next;
	}
	return (0);
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
	while (current_node)
	{
		next_node = current_node->next;
		append_env_node(&shell->env, current_node);
		current_node = next_node;
	}
	free_env_list(&export);
}
