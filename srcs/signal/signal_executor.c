#include "../../include/minishell.h"

void	signal_handler_execve(int signum)
{
	if (signum == SIGINT)
		g_exit_status = 130;
	if (signum == SIGQUIT)
		g_exit_status = 131;
}