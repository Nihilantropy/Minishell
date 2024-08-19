#include "../../include/minishell.h"

void	sigquit_handler(int sig)
{
	struct sigaction	sa;

	(void)sig;
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
}
