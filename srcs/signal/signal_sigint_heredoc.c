#include "../../include/minishell.h"

static void	handle_sigint_heredoc(int sig);

/*	signal handler:
**	Capture the SIGNINT signal and
**	make it reset user prompt
*/
void	sigint_handler_heredoc(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigint_heredoc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
}

static void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	exit(HERE_DOC_SIGINT);
}
