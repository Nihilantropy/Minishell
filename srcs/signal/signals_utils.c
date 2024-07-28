#include "../../include/minishell.h"

void	handle_enter(t_shell *shell)
{
	(void)shell;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	return ;
}
