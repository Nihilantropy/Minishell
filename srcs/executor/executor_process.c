#include "../../include/minishell.h"

static void	process_pipeline(t_shell *shell, t_cmd *current_node, int fd[2]);
void		handle_exit_status(t_shell *shell, int status);

void process_command(t_shell *shell)
{
	int		fd[2];
	t_cmd	*current_node;
	pid_t	pid;
	int		status;

	current_node = shell->cmd;
	while (current_node)
	{
		if (pipe(fd) == -1)
			ft_exit_error(ERR_PIPE);
		pid = fork();
		if (pid == -1)
			ft_exit_error(ERR_FORK);
		if (pid == 0)
			process_pipeline(shell, current_node, fd);
		else
		{
			close(fd[1]);
			if (current_node->next)
				dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			current_node = current_node->next;
		}
	}
	while (wait(&status) > 0)
		handle_exit_status(shell, status);
	exit(EXIT_SUCCESS);
}

static void	process_pipeline(t_shell *shell, t_cmd *current_node, int fd[2])
{
	if (current_node->next)
		dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	redir_input(current_node->redir);
	redir_output(current_node->redir);
	if (current_node->builtin.is_builtin)
		handle_builtin(shell, current_node);
	else if (current_node->matrix[0])
		exe_cmd(shell, current_node);
	else
		ft_exit_error("");
	exit(EXIT_SUCCESS);
}
