#include "../../include/minishell.h"

static void	search_here_doc(t_shell *shell, t_arg *arg);

void	handle_history(t_shell *shell)
{
	search_here_doc(shell, shell->arg);
	if (shell->add_to_history)
		add_history(shell->line);
	shell->add_to_history = true;
}

static void	search_here_doc(t_shell *shell, t_arg *arg)
{
	t_arg	*current_node;

	current_node = arg;
	if (!current_node)
		return ;
	while (current_node)
	{
		if (current_node->token.t_here_doc)
			shell->add_to_history = false;
		current_node = current_node->next;
	}
}
