#include "../../include/minishell.h"

static char	*find_cmd_path(t_shell *shell, t_cmd *current_node);

void	exe_cmd(t_shell *shell, t_cmd *current_node)
{
	char	*cmd_path;

	cmd_path = find_cmd_path(shell, current_node);
	if (!cmd_path)
	{
		printf("%s: command not found\n", current_node->matrix[0]);
		exit(EXIT_FAILURE);
	}
	if (execve(cmd_path, current_node->matrix, shell->envp_d) == -1)
	{
		perror("execve failed\n");
		exit(EXIT_FAILURE);
	}
}

static char	*find_cmd_path(t_shell *shell, t_cmd *current_node)
{
	int		i;
	char	*relative_path;
	char	*cmd_path;

	i = 0;
	while (shell->path[i])
	{
		relative_path = ft_strjoin(shell->path[i], "/");
		cmd_path = ft_strjoin(relative_path, current_node->matrix[0]);
		free(relative_path);
		if (!cmd_path)
			return (NULL);
		if (access(cmd_path, F_OK) == 0)
		{
			free_matrix(shell->path);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	free_matrix(shell->path);
	return (NULL);
}
