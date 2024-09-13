#include "../../include/minishell.h"

void	signal_sigterm(t_shell *shell)
{
	free_prompt(shell);
	free_shell(shell);
	exit(EXIT_SUCCESS);
}
