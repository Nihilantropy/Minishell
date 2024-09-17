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
