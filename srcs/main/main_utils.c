#include "../../include/minishell.h"

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
