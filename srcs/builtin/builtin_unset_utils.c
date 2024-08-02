#include "../../include/minishell.h"

static t_env	*create_unset_node(t_env **unset);
static char		*ft_copy_ex_name(char *current_var);

void	create_unset_list(char **matrix, t_env **unset)
{
	char	**matrix_copy;
	int		y;
	t_env	*current_node;

	matrix_copy = dup_matrix(matrix);
	if (!matrix_copy)
		ft_exit_error(ERR_ALLOC_MATRIX_COPY);
	y = 0;
	while (matrix_copy[y])
	{
		current_node = create_unset_node(unset);
		current_node->var = copy_ex_var(matrix[y]);
		current_node->name = ft_copy_ex_name(current_node->var);
		y++;
	}
	free_matrix(matrix_copy);
}

static t_env	*create_unset_node(t_env **unset)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		ft_exit_error(ERR_ALLOR_EXPORT);
	new_node->var = NULL;
	new_node->name = NULL;
	new_node->value = NULL;
	new_node->show = false;
	append_env_node(unset, new_node);
	return (new_node);
}

static char	*ft_copy_ex_name(char *current_var)
{
	int		i;
	char	*name;

	i = 0;
	while (current_var[i] && current_var[i] != '=')
		i++;
	if (current_var[i] == '=')
		i--;
	name = malloc(i + 1);
	if (!name)
		ft_exit_error(ERR_ALLOC_NAME);
	ft_strlcpy(name, current_var, i + 1);
	return (name);
}