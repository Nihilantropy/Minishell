#include "../../include/minishell.h"

/*
	Replace SIGQUIT signal with SIG_IGN to do nothing
*/
void	sigquit_handler(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
}
