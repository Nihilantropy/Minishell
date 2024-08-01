#include "../../include/minishell.h"

void	signal_sigterm(t_shell *shell)
{
	free_prompt_lists(shell);
	free_shell_lists(shell);
	printf("exit EOF\n");
	exit(EXIT_SUCCESS);
}
