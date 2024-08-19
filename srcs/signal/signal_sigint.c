#include "../../include/minishell.h"

static void	sigint_handler(int sig);
static void	handle_sigint(int sig);

void	signal_handler(void)
{
	sigint_handler(SIGINT);
	sigquit_handler(SIGQUIT);
}

static void	sigint_handler(int sig)
{
	struct sigaction	sa;

	(void)sig;
	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
}

static void	handle_sigint(int sig)
{
	(void)sig;
	printf("EVVIVA! handle sigint  main \n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	printf("\n\nminishell$ ");
}
