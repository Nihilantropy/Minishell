#include "../../include/minishell.h"

static int	check_token_index(t_shell *shell);
static void	syntax_error_near_token(t_shell *shell, char *str);

int	check_arg_list(t_shell *shell)
{
	if (shell->arg->token.pipe)
	{
		printf("-bash: syntax error near unexpected token `%s'\n", shell->arg->str);
		shell->last_exit_status = 2;
		shell->error = true;
		return (1);
	}
	if (check_token_index(shell))
		return (1);
	return (0);
}

static int	check_token_index(t_shell *shell)
{
	t_arg	*current_node;
	t_arg	*next_node;

	current_node = shell->arg;
	while (current_node)
	{
		next_node = current_node->next;
		if (current_node->token.is_token && !next_node)
		{
			syntax_error_near_token(shell, current_node->str);
			return (1);
		}
		else if (next_node && ((current_node->token.is_token && !current_node->token.pipe) 
					&& next_node->token.is_token))
		{
			syntax_error_near_token(shell, next_node->str);
			return (1);
		}
		current_node = current_node->next;
	}
	return (0);
}

static void	syntax_error_near_token(t_shell *shell, char *str)
{
	printf("-bash: syntax error near unexpected token `%s'\n", str);
	shell->last_exit_status = 2;
	shell->error = true;
}
