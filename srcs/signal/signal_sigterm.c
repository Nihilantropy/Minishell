#include "../../include/minishell.h"

void	signal_sigterm(t_shell *shell)
{
	free_prompt(shell);
	free_shell(shell);
	printf("exit EOF\n");
	exit(EXIT_SUCCESS);
}
