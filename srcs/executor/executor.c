#include "../../include/minishell.h"

void	executor(t_shell *shell)
{
	int		stdin_copy;
	int		stdout_copy;
	pid_t	pid;
	
	stdin_copy = dup(STDIN_FILENO);
	stdout_copy = dup(STDOUT_FILENO);
	pid = fork();
	if (pid == -1)
		ft_exit_error("Fork error\n");
	if (pid == 0)
	{
		process_command(shell);
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, NULL, 0);
	reset_redir(stdin_copy, stdout_copy);
}
