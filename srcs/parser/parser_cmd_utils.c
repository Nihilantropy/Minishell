#include "../../include/minishell.h"

static char	*join_matrix_to_node(char *str, char *to_join);

/*
	Return the length of the command + flags untill the end or the pipe
*/
int	len_to_pipe_cmd(t_arg *arg)
{
	int		len;
	t_arg	*current_node;

	len = 0;
	current_node = arg;
	while (current_node && !current_node->token.pipe)
	{
		if (!(current_node->token.is_token || current_node->type.is_redir))
		{
			if (!current_node->prev || !current_node->prev->chained)
				len++;
		}
		current_node = current_node->next;
	}
	return (len);
}

/*
	1) Copy the command + flags untill the end or the pipe
	2) If the current node is a pipe, move the node to the next one
	3) Move the head of the arg list to the current node
*/
void	copy_command(t_cmd *cmd, t_shell *shell)
{
	int		y;
	t_arg	*current_node;

	y = 0;
	current_node = shell->arg;
	while (current_node && !current_node->token.pipe)
	{
		if (!(current_node->token.is_token || current_node->type.is_redir))
		{
			if (current_node->prev && current_node->prev->chained)
				cmd->matrix[y - 1] = join_matrix_to_node(cmd->matrix[y - 1], current_node->str);
			else
				cmd->matrix[y++] = ft_strdup(current_node->str);
		}
		current_node = current_node->next;
	}
	cmd->matrix[y] = NULL;
	if (current_node && current_node->token.pipe && current_node->next)
		current_node = current_node->next;
	shell->arg = current_node;
}

static char	*join_matrix_to_node(char *str, char *to_join)
{
	char	*joined_str;

	joined_str = ft_strjoin(str, to_join);
	free(str);
	return (joined_str);
}