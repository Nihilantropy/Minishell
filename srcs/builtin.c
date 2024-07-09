#include "../include/minishell.h"

void	handle_builtin(t_shell *shell, char **envp)
{
	handle_export(shell, envp);
}

void check_builtin(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->matrix[0], "export"))
		cmd->builtin.export = true;
	else if (!ft_strcmp(cmd->matrix[0], "cd"))
		cmd->builtin.cd = true;
	else if (!ft_strcmp(cmd->matrix[0], "pwd"))
		cmd->builtin.cd = true;
	else if (!ft_strcmp(cmd->matrix[0], "cd"))
		cmd->builtin.cd = true;
	else if (!ft_strcmp(cmd->matrix[0], "cd"))
		cmd->builtin.cd = true;
	else if (!ft_strcmp(cmd->matrix[0], "cd"))
		cmd->builtin.cd = true;
	if (cmd->builtin.cd || cmd->builtin.echo
		|| cmd->builtin.pwd || cmd->builtin.exit
		|| cmd->builtin.env || cmd->builtin.export
		|| cmd->builtin.unset)
		cmd->builtin.is_builtin = true;
}
