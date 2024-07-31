#include "../../include/minishell.h"

static void	handle_single_builtin_cmd(t_shell *shell);

/*
	1) Make a copy of the STDIN and STDOUT to reset after each command
	2) Fork the main process to execute the list of command
	3) reset the redirection to the STDIN and STDOUT
*/
void	executor(t_shell *shell)
{
	pid_t	pid;
	int		status;
	shell->stdin_copy = dup(STDIN_FILENO);
	shell->stdout_copy = dup(STDOUT_FILENO);

	if (shell->pipes_nbr == 0 && shell->cmd->builtin.is_builtin)
	{
		handle_single_builtin_cmd(shell);
	}
	else
	{
		pid = fork();
		if (pid == -1)
			ft_exit_error(ERR_FORK);
		if (pid == 0)
		{
			process_command(shell);
			exit(EXIT_SUCCESS);
		}
		waitpid(pid, &status, 0);
	}
	shell->last_exit_status = status;
	reset_redir(shell);
	free_prompt_lists(shell);
}

/*
	If only one cmd is called and it's a builtin,
	handle it.
*/
static void	handle_single_builtin_cmd(t_shell *shell)
{
	t_cmd	*current_node;

	current_node = shell->cmd;
	redir_input(shell, current_node->redir);
	redir_output(current_node->redir);
	if (!shell->path)
	{
		printf("-bash: %s: No such file or directory\n", current_node->matrix[0]);
		return ;
	}
	handle_builtin(shell, current_node);
}