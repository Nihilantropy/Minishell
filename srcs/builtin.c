#include "../include/minishell.h"

void	handle_builtin(t_shell *shell)
{
	if (!ft_strcmp(shell->cmd->matrix[0], "export") && shell->pipes_nbr == 0)
		handle_export(shell);
}

void check_builtin(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->matrix[0], "echo"))
		cmd->builtin.echo = true;
	else if (!ft_strcmp(cmd->matrix[0], "cd"))
		cmd->builtin.cd = true;
	else if (!ft_strcmp(cmd->matrix[0], "pwd"))
		cmd->builtin.pwd = true;
	else if (!ft_strcmp(cmd->matrix[0], "export"))
		cmd->builtin.export = true;
	else if (!ft_strcmp(cmd->matrix[0], "unset"))
		cmd->builtin.unset = true;
	else if (!ft_strcmp(cmd->matrix[0], "env"))
		cmd->builtin.env = true;
	else if (!ft_strcmp(cmd->matrix[0], "exit"))
		cmd->builtin.exit = true;
	if (cmd->builtin.echo || cmd->builtin.cd
		|| cmd->builtin.pwd || cmd->builtin.export
		|| cmd->builtin.unset || cmd->builtin.env
		|| cmd->builtin.exit)
		cmd->builtin.is_builtin = true;
}
