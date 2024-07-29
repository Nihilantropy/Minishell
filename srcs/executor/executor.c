#include "../../include/minishell.h"

static void	handle_single_builtin_cmd(t_shell *shell);

void	executor(t_shell *shell)
{
	pid_t	pid;
	int		stdin_copy;
	int		stdout_copy;
	
	stdin_copy = dup(STDIN_FILENO);
	stdout_copy = dup(STDOUT_FILENO);
	if (shell->pipes_nbr == 0 && shell->cmd->builtin.is_builtin)
		handle_single_builtin_cmd(shell);
	else
	{
		pid = fork();
		if (pid == -1)
			ft_exit_error("Fork error\n");
		if (pid == 0)
		{
			process_command(shell);
			exit(EXIT_SUCCESS);
		}
		waitpid(pid, NULL, 0);
	}
	reset_redir(shell, stdin_copy, stdout_copy);
}

static void	handle_single_builtin_cmd(t_shell *shell)
{
	t_cmd	*current_node;

	current_node = shell->cmd;
	redir_input(current_node->redir);
	redir_output(current_node->redir);
	handle_builtin(shell, current_node);
}