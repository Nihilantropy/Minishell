#include "../../include/minishell.h"

static void	sigint_handler(int signum);
static void	handle_sigint(int sig);

void	signal_handler(void)
{
	sigint_handler(SIGINT);
}

static void	sigint_handler(int signum)
{
	struct sigaction sa;

	(void)signum;
	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
}

static void	handle_sigint(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	printf("\n\nminishell$ ");
}