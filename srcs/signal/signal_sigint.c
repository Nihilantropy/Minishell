#include "../../include/minishell.h"

static void	handle_sigint(int sig);

/*
	Replace SIGNINT signal to reset user prompt
*/
void	sigint_handler(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
}

static void	handle_sigint(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	printf("ctrl + c pressed\n");
	printf("\n\nminishell$ ");
}
