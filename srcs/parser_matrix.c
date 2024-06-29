#include "../include/minishell.h"

static int	len_to_pipe(t_arg **current_head);
static void	init_matrix_z(t_shell *shell, char ***matrix);
static void	matrix_point_to_str(t_shell *shell, char ***matrix, t_arg **current_head, t_arg *arg);

void	parse_matrix(t_shell *shell, t_arg *arg)
{
	int		z;
	int 	y;
	int		j;
	t_arg	**current_head;

	z = 0;
	j = 0;
	current_head = &arg;
	shell->matrix = (char ***)malloc(sizeof(char **) * (shell->pipes_nbr + 2));
	if (!shell->matrix)
		ft_exit_error(ERR_ALLOC_MATRIX);
	init_matrix_z(shell, shell->matrix);
	while (z <= shell->pipes_nbr)
	{
		y = len_to_pipe(current_head);
		shell->matrix[z] = (char **)malloc(sizeof(char *) * (y + 1));
		if (!shell->matrix[z])
			ft_exit_error(ERR_ALLOC_MATRIX);
		while (j <= y)
			shell->matrix[z][j++] = NULL;
		z++;
	}
	current_head = &arg;
	matrix_point_to_str(shell, shell->matrix, current_head, arg);
	print_matrix(shell->matrix);
}

static void	init_matrix_z(t_shell *shell, char ***matrix)
{
	int	z;

	z = 0;
	while (z < shell->pipes_nbr + 2)
		matrix[z++] = NULL;
}

static int	len_to_pipe(t_arg **current_head)
{
	int			i;
	t_arg		*current_node;

	i = 0;
	current_node = *current_head;
	while (current_node && !current_node->token.pipe)
	{
		if (!current_node->token.t_infile
			&& !current_node->token.t_outfile
			&& !current_node->token.t_here_doc
			&& !current_node->token.t_append)
			i++;
		current_node = current_node->next;
	}
	if (current_node && current_node->next)
		*current_head = current_node->next;
	else
		*current_head = NULL;
	return (i);
}

static void	matrix_point_to_str(t_shell *shell, char ***matrix, t_arg **current_head, t_arg *arg)
{
	int	z;
	int	y;
	int	j;
	t_arg *current_node;

	z = 0;
	current_node = arg;
	while ((z <= shell->pipes_nbr + 2) && current_node)
	{
		y = 0;
		j = len_to_pipe(current_head);
		while ((y <= j) && current_node)
		{
			if (!current_node->token.t_infile
				&& !current_node->token.t_outfile
				&& !current_node->token.t_here_doc
				&& !current_node->token.t_append
				&& !current_node->token.pipe)
			{
				matrix[z][y] = current_node->str;
				printf("matrix[%d][%d] is: %s\n", z, y, matrix[z][y]);
				y++;
			}
			if (current_node->token.pipe)
				break;
			current_node = current_node->next;
		}
		z++;
		if (current_node && current_node->token.pipe)
			current_node = current_node->next;
	}
}