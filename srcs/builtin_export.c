#include "../include/minishell.h"

static int	matrix_length(char **matrix)
{
	int	y;
	int	x;

	y = 0;
	while (matrix[y])
	{
		x = 0;
		while (matrix[y][x])
			x++;
		y++;
	}
	return (y);
}

static char	**copy_matrix(char **matrix)
{
	int		len;
	char	**matrix_copy;
	int		y;

	len = matrix_length(matrix);
	matrix_copy = (char **)malloc(sizeof(char *) * (len + 1));
	if (!matrix_copy)
		ft_exit_error(ERR_ALLOC_MATRIX_COPY);
	y = 0;
	while (y < len)
	{
		matrix_copy[y] = ft_strdup(matrix[y]);
		y++;
	}
	matrix_copy[y] = NULL;
	return (matrix_copy);
}

void	handle_export(t_shell *shell, char **envp)
{
	char	**envp_copy;

	envp_copy = copy_matrix(envp);
	print_matrix(envp_copy);
	ft_putnl();
	(void)shell;
}