#include "../include/minishell.h"

static void	print_echo_matrix(char **echo_matrix, t_bool flag);

void	handle_builtin_echo(t_shell *shell, char **matrix)
{
	char	**echo_matrix;
	t_bool	flag;

	(void)shell;
	echo_matrix = dup_matrix(matrix);
	if (!echo_matrix)
		ft_exit_error(ERR_ALLOC_MATRIX_COPY);
	flag = false;
	if (!ft_strncmp(echo_matrix[1], "-n", 3))
		flag = true;
	if (flag)
		print_echo_matrix(echo_matrix + 2, flag);
	else
		print_echo_matrix(echo_matrix + 1, flag);
	free_matrix(echo_matrix);
}

static void	print_echo_matrix(char **echo_matrix, t_bool flag)
{
	int	y;

	y = 0;
	while (echo_matrix[y])
	{
		if (echo_matrix[y + 1])
			printf("%s ", echo_matrix[y]);
		else
			printf("%s", echo_matrix[y]);
		y++;
	}
	if (flag == false)
		printf("\n");
}