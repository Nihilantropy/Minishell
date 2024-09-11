#include "../../include/minishell.h"

/*	init shell:
**	init the main shell structure.
*/
void	init_shell(t_shell *shell, char **envp)
{
	shell->line = NULL;
	shell->add_to_history = true;
	shell->arg = NULL;
	shell->pipes_nbr = 0;
	shell->env = NULL;
	shell->new_env = NULL;
	init_env(shell, envp);
	shell->path = NULL;
	shell->last_exit_status = 0;
	shell->cmd = NULL;
	shell->error = false;
}
