#include "../../include/minishell.h"

/*
	Init the main shell struct
*/
void	init_shell(t_shell *shell, char **envp)
{
	shell->line = NULL;
	shell->add_to_history = true;
	shell->arg = NULL;
	shell->pipes_nbr = 0;
	shell->env = NULL;
	init_env(shell, envp);
	shell->path = NULL;
	shell->last_exit_status = 0;
	shell->cmd = NULL;
	shell->error = false;
	shell->envp_d = envp;
}
