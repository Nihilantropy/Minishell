#include "../include/minishell.h"

static void	print_env_builtin(t_env *env);

void	handle_builtin_env(t_shell *shell)
{
	print_env_builtin(shell->env);
	return ;
}

static void	print_env_builtin(t_env *env)
{
	t_env	*current_node;

	current_node = env;
	while (current_node)
	{
		if (!current_node->show)
			current_node = current_node->next;
		else
		{
			printf("%s=%s\n", current_node->name, current_node->value);
			current_node = current_node->next;
		}
	}
}