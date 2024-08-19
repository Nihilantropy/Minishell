#include "../../include/minishell.h"

static void	child_proc_sigint_handler(int sig);
static void	child_proc_handle_sigint(int sig);
static void	child_proc_sigquit_handler(int sig);

void	child_proc_signal_handler(void)
{
	child_proc_sigint_handler(SIGINT);
	child_proc_sigquit_handler(SIGQUIT);
}

static void	child_proc_sigint_handler(int sig)
{
	struct sigaction	sa;

	(void)sig;
	sa.sa_handler = child_proc_handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}

static void	child_proc_handle_sigint(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	printf("\n\nminishell$ ");
	exit(EXIT_SUCCESS);
}

static void	child_proc_sigquit_handler(int sig)
{
	struct sigaction	sa;

	(void)sig;
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}
