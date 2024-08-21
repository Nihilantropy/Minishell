#include "../../include/minishell.h"

static int	check_exit_invalid_arg(t_shell *shell);
static int	check_exit_alpha_arg(char **matrix);
static int	check_exit_multi_arg(char **matrix);

void	handle_builtin_exit(t_shell *shell)
{
	if (check_exit_invalid_arg(shell) == 0)
	{
		free_shell(shell);
		free_prompt(shell);
		exit(EXIT_SUCCESS);
	}
	else
		return ;
	return ;
}

static int	check_exit_invalid_arg(t_shell *shell)
{
	char	**matrix;

	matrix = shell->cmd->matrix;
	if (shell->pipes_nbr != 0)
		return (1);
	if (!matrix[1])
		return (0);
	if (check_exit_alpha_arg(matrix) == 0)
		return (1);
	if (check_exit_multi_arg(matrix) == 1)
		return (1);
	return (0);
}

static int	check_exit_alpha_arg(char **matrix)
{
	int	x;

	x = 0;
	while (matrix[1][x])
	{
		if (!ft_isdigit(matrix[1][x]))
		{
			printf("-minishell: exit: %s: ", matrix[1]);
			printf("numeric argument required\n");
			return (0);
		}
		x++;
	}
	return (1);
}

static int	check_exit_multi_arg(char **matrix)
{
	if (matrix[2] != NULL)
	{
		printf("too many arguments\n");
		return (1);
	}
	return (0);
}
