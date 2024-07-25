#include "../include/minishell.h"

static void	print_echo_matrix(char **echo_matrix, t_bool flag);
static void	handle_echo_print(char **echo_matrix);

void	handle_builtin_echo(t_shell *shell, char **matrix)
{
	char	**echo_matrix;

	echo_matrix = dup_matrix(matrix);
	if (!echo_matrix)
		ft_exit_error(ERR_ALLOC_MATRIX_COPY);
	handle_echo_print(echo_matrix);
	free_matrix(echo_matrix);
	shell->last_exit_status = EXIT_STATUS_SUCCESS;
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

static void	handle_echo_print(char **echo_matrix)
{
	t_bool	flag;

	flag = false;
	if (echo_matrix[1] && !ft_strncmp(echo_matrix[1], "-n", 3))
		flag = true;
	if (flag && !echo_matrix[2])
		printf("echo -n with no string to output\n"); // TODO remove the print
	else if (!flag && !echo_matrix[1])
		printf("echo with no string to output\n"); // TODO remove the print
	else if (flag && echo_matrix[2])
		print_echo_matrix(echo_matrix + 2, flag);
	else
		print_echo_matrix(echo_matrix + 1, flag);
}