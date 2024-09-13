#include "../../include/minishell.h"

/*	signal handler interactive:
**	Handle signals SIGINT & SIGQUIT for interactive mode
*/
void	signal_handler_interactive(void)
{
	sigint_handler();
	sigquit_handler();
}
