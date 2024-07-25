#include "../include/minishell.h"

void	executor(t_shell *shell, char **envp)
{
	t_cmd	*current_node;

	current_node = shell->cmd;
	while (current_node)
	{
		if (current_node->builtin.is_builtin)
			handle_builtin(current_node);
		else
			printf("Current command not a builtin. Execute normally.\n");
		current_node = current_node->next;
	}
}