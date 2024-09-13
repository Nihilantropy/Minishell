#include "../../include/minishell.h"

/*	signal handler interactive:
**	Handle signals SIGINT & SIGQUIT for interactive mode
*/
void	signal_handler_interactive(void)
{
	sigint_handler();
	sigquit_handler();
}

static void	signal_print_newline(int sig);

/*	signal handler non-interactive:
**	Handle signals SIGINT & SIGQUIT for non-interactive mode
*/
void	signal_handler_non_interactive(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &signal_print_newline;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

static void	signal_print_newline(int sig)
{
	(void)sig;
	rl_on_new_line();
}

void	handleback(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	exit(137);
}
