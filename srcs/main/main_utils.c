#include "../../include/minishell.h"

void	free_prompt_lists(t_shell *shell)
{
	if (shell->line && shell->line[0] == '\0')
	{
		free(shell->line);
		shell->line = NULL;
		return ;
	}
	if (shell->cmd)
		free_all_redir_list(shell->cmd);
	if (shell->cmd)
		free_cmd_list(&shell->cmd);
	if (shell->arg)
		free_list(&shell->arg);
	if (shell->path)
	{
		free_matrix(shell->path);
		shell->path = NULL;
	}
}

void	free_shell_lists(t_shell *shell)
{
	if (shell->env)
		free_env_list(&shell->env);
}

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
	copy_matrix[y] = '\0';
	return (copy_matrix);
}

void	free_matrix(char **matrix)
{
	int	y;

	y = 0;
	while (matrix[y])
		free(matrix[y++]);
	free(matrix);
}