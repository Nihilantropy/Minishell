#include "../include/minishell.h"

void	handle_builtin_exit(t_shell *shell)
{
	printf(EXIT_MAIN);
	free_shell_lists(shell);
	shell->last_exit_status = EXIT_STATUS_SUCCESS;
	exit(EXIT_SUCCESS);
}