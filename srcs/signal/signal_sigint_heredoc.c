#include "../../include/minishell.h"

static void	handle_sigint_heredoc(int sig);

/*	signal handler:
**	Capture the SIGNINT signal and
**	make it reset user prompt
*/
void	sigint_handler_heredoc(void)
{
    signal(SIGINT, handle_sigint_heredoc);
}

static void	handle_sigint_heredoc(int sig)
{
	(void)sig;
    rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	exit(EXIT_FAILURE);
}