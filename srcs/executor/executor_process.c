#include "../../include/minishell.h"

static void	process_child(t_shell *shell, t_cmd *current_node, int fd[2]);
static void	process_parent(t_shell *shell, t_cmd *current_node);

void	process_command(t_shell *shell)
{
	int		fd[2];
	int		i;
	t_cmd	*current_node;

	i = 0;
	current_node = shell->cmd;
	while (i < shell->pipes_nbr)
	{
		if (pipe(fd) == -1)
			ft_exit_error("PIPE ERROR\n");
		process_child(shell, current_node, fd);
		close(fd[1]);
		if (i < (shell->pipes_nbr))
			dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		current_node = current_node->next;
		i++;
	}
	process_parent(shell, current_node);
	wait(NULL);
}

static void	process_child(t_shell *shell, t_cmd *current_node, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_exit_error("FORK_ERROR");
	if (pid == 0)
	{
		if (current_node->next)
			dup2(fd[1], STDOUT_FILENO);
		redir_input(current_node->redir);
		redir_output(current_node->redir);
		close(fd[0]);
		if (current_node->builtin.is_builtin)
		{
			handle_builtin(shell, current_node);
			exit(EXIT_SUCCESS);
		}
		else
			exe_cmd(shell, current_node);
	}
}

static void	process_parent(t_shell *shell, t_cmd *current_node)
{
	redir_input(current_node->redir);
	redir_output(current_node->redir);
	if (current_node->builtin.is_builtin)
	{
		handle_builtin(shell, current_node);
		exit(EXIT_SUCCESS);
	}
	else
		exe_cmd(shell, current_node);
}
