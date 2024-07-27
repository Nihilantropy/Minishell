#include "../../include/minishell.h"

/*
	Enter the correct builtin
*/
void	handle_builtin(t_shell *shell, t_cmd *current_node)
{
	if (current_node->builtin.export)
		handle_builtin_export(shell, current_node->matrix);
	else if (current_node->builtin.env)
		handle_builtin_env(shell);
	else if (current_node->builtin.unset)
		handle_builtin_unset(shell, current_node->matrix);
	else if (current_node->builtin.echo)
		handle_builtin_echo(shell, current_node->matrix);
	else if (current_node->builtin.pwd)
		handle_builtin_pwd(shell);
	else if (current_node->builtin.exit)
		handle_builtin_exit(shell);
	else if (current_node->builtin.cd)
		handle_builtin_cd(shell, current_node->matrix);
}

/*
	Set the right builtin type for the current node
*/
void check_builtin(t_cmd *current_node)
{
	if (!current_node->matrix[0])
		return ;
	if (!ft_strncmp(current_node->matrix[0], "echo", 5))
		current_node->builtin.echo = true;
	else if (!ft_strncmp(current_node->matrix[0], "cd", 3))
		current_node->builtin.cd = true;
	else if (!ft_strncmp(current_node->matrix[0], "pwd", 4))
		current_node->builtin.pwd = true;
	else if (!ft_strncmp(current_node->matrix[0], "export", 7))
		current_node->builtin.export = true;
	else if (!ft_strncmp(current_node->matrix[0], "unset", 6))
		current_node->builtin.unset = true;
	else if (!ft_strncmp(current_node->matrix[0], "env", 4))
		current_node->builtin.env = true;
	else if (!ft_strncmp(current_node->matrix[0], "exit", 5))
		current_node->builtin.exit = true;
	if (current_node->builtin.echo || current_node->builtin.cd
		|| current_node->builtin.pwd || current_node->builtin.export
		|| current_node->builtin.unset || current_node->builtin.env
		|| current_node->builtin.exit)
		current_node->builtin.is_builtin = true;
}
