#include "../include/minishell.h"

/*
	Enter the correct builtin
*/
void	handle_builtin(t_shell *shell)
{
	if (!ft_strcmp(shell->cmd->matrix[0], "export") && shell->pipes_nbr == 0)
		handle_export(shell);
}

/*
	Set the right builtin type for the current node
*/
void check_builtin(t_cmd *current_node)
{
	if (!ft_strcmp(current_node->matrix[0], "echo"))
		current_node->builtin.echo = true;
	else if (!ft_strcmp(current_node->matrix[0], "cd"))
		current_node->builtin.cd = true;
	else if (!ft_strcmp(current_node->matrix[0], "pwd"))
		current_node->builtin.pwd = true;
	else if (!ft_strcmp(current_node->matrix[0], "export"))
		current_node->builtin.export = true;
	else if (!ft_strcmp(current_node->matrix[0], "unset"))
		current_node->builtin.unset = true;
	else if (!ft_strcmp(current_node->matrix[0], "env"))
		current_node->builtin.env = true;
	else if (!ft_strcmp(current_node->matrix[0], "exit"))
		current_node->builtin.exit = true;
	if (current_node->builtin.echo || current_node->builtin.cd
		|| current_node->builtin.pwd || current_node->builtin.export
		|| current_node->builtin.unset || current_node->builtin.env
		|| current_node->builtin.exit)
		current_node->builtin.is_builtin = true;
}
