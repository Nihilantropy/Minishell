#include "../include/minishell.h"

void	handle_enter(t_shell *shell)
{
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	free(shell->line);
	return ;
}

void	count_pipes(t_shell *shell)
{
	int	y;

	if (shell->matrix[0][0] == '|')
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		free_matrix(shell->matrix);
		return ;
	}
	y = 0;
	while (shell->matrix[y])
		y++;
	shell->cmd.pipes_nbr = y - 1;
	printf("pipes number: %d\n", shell->cmd.pipes_nbr);
}

void	remove_spaces(char **matrix)
{
	int		y;
	char	*new_string;

	y = 0;
	while (matrix[y])
	{
		new_string = ft_strtrim(matrix[y], " \t");
		if (new_string)
		{
			free(matrix[y]);
			matrix[y] = new_string;
		}
		y++;
	}
}