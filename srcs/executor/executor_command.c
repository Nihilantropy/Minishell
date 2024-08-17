#include "../../include/minishell.h"

char		*find_cmd_path(t_shell *shell, t_cmd *current_node);
int			check_relative_path(t_cmd *current_node);
char		*extract_cmd(t_cmd *current_node);
void		check_path(t_shell *shell, t_cmd *current_node);
static void	handle_relative_path(t_shell *shell, t_cmd *current_node);
static void	handle_env_path(t_shell *shell, t_cmd *current_node);

/*
	Handle relative and env path for the commands
*/
void	exe_cmd(t_shell *shell, t_cmd *current_node)
{
	if (check_relative_path(current_node))
		handle_relative_path(shell, current_node);
	else
		handle_env_path(shell, current_node);
}

static void	handle_relative_path(t_shell *shell, t_cmd *current_node)
{
	char	*cmd;
	char	*cmd_path;

	cmd = extract_cmd(current_node);
	cmd_path = current_node->matrix[0];
	current_node->matrix[0] = cmd;
	if (access(cmd_path, F_OK) != 0)
	{
		perror("minishell: no such file or directory\n");
		free(cmd_path);
		free_matrix(shell->path);
		exit(EXIT_FAILURE);
	}
	if (execve(cmd_path, current_node->matrix, shell->new_env) == -1)
	{
		perror("execve failed\n");
		exit(EXIT_FAILURE);
	}
}

static void	handle_env_path(t_shell *shell, t_cmd *current_node)
{
	char	*cmd_path;

	check_path(shell, current_node);
	cmd_path = find_cmd_path(shell, current_node);
	if (!cmd_path)
	{
		printf("EVVIVA!\n");
		printf("%s: command not found\n", current_node->matrix[0]);
		exit(EXIT_FAILURE);
	}
	if (execve(cmd_path, current_node->matrix, shell->new_env) == -1)
	{
		perror("execve failed\n");
		exit(EXIT_FAILURE);
	}
}
