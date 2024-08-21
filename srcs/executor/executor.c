#include "../../include/minishell.h"

static void	handle_single_builtin_cmd(t_shell *shell);
void		handle_exit_status(t_shell *shell, int status);

/*
	1) Make a copy of the STDIN and STDOUT to reset after each list of commands
	2) Fork the main process to execute the list of command
	3) reset the redirection to the STDIN and STDOUT
*/
void	executor(t_shell *shell)
{
	pid_t	pid;
	int		status;

	shell->stdin_copy = dup(STDIN_FILENO);
	shell->stdout_copy = dup(STDOUT_FILENO);
	if (shell->stdin_copy == -1 || shell->stdout_copy == -1)
		perror("dup");
	if (shell->pipes_nbr == 0 && shell->cmd->builtin.is_builtin)
		handle_single_builtin_cmd(shell);
	else
	{
		pid = fork();
		if (pid == -1)
			ft_exit_error(ERR_FORK);
		if (pid == 0)
			process_command(shell);
		waitpid(pid, &status, 0);
		handle_exit_status(shell, status);
	}
	reset_redir(shell);
	free_prompt(shell);
}

/*
	If only one cmd is called and it's a builtin,
	handle it.
*/
static void	handle_single_builtin_cmd(t_shell *shell)
{
	t_cmd	*current_node;

	current_node = shell->cmd;
	redir_input(current_node->redir);
	redir_output(current_node->redir);
	if (!shell->path)
	{
		ft_putstr_fd("-minishell: ", 2);
		ft_putstr_fd(current_node->matrix[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return ;
	}
	handle_builtin(shell, current_node);
}

void	handle_exit_status(t_shell *shell, int status)
{
	if (WIFEXITED(status))
		shell->last_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->last_exit_status = 128 + WTERMSIG(status);
	else
		shell->last_exit_status = 1;
}
