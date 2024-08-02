#include "../../include/minishell.h"

static void	child_proc_sigint_handler(int sig);
static void	child_proc_handle_sigint(int sig);

void	child_proc_signal_handler(t_shell * shell)
{
	(void)shell;
	child_proc_sigint_handler(SIGINT);
}

static void	child_proc_sigint_handler(int signum)
{
	struct sigaction sa;

	(void)signum;
	sa.sa_handler = child_proc_handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
}

static void	child_proc_handle_sigint(int sig)
{
	(void)sig;
	ft_exit_success("\nSIGINT called on child process\n");
}
