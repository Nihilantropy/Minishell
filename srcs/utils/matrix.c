#include "../../include/minishell.h"

void	print_matrix(char **matrix)
{
	int	y;

	y = 0;
	while (matrix[y])
	{
		printf("matrix[%d]: %s\n", y, matrix[y]);
		y++;
	}
}

void	free_matrix(char **matrix)
{
	int	y;

	y = 0;
	if (!matrix[y])
		return ;
	while (matrix[y])
		free(matrix[y++]);
	free(matrix);
	matrix = NULL;
}

int	matrix_len(char **matrix)
{
	int	len;

	len = 0;
	while (matrix[len])
		len++;
	return (len);
}

char	**dup_matrix(char **matrix)
{
	char	**copy_matrix;
	int		y;

	copy_matrix = NULL;
	y = 0;
	while (matrix[y])
		y++;
	copy_matrix = malloc(sizeof(char *) * (y + 1));
	if (!copy_matrix)
		ft_exit_error(ERR_ALLOC_MATRIX_COPY);
	y = 0;
	while (matrix[y])
	{
		copy_matrix[y] = ft_strdup(matrix[y]);
		y++;
	}
	copy_matrix[y] = NULL;
	return (copy_matrix);
}
