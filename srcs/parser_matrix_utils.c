#include "../include/minishell.h"

int	len_to_pipe_cmd(t_arg *arg)
{
	int		len;
	t_arg	*current_node;

	len = 0;
	current_node = arg;
	while (current_node && !current_node->token.pipe)
	{
		if (!(current_node->token.t_infile || current_node->token.t_outfile
			|| current_node->token.t_here_doc || current_node->token.t_append
			|| current_node->type.infile || current_node->type.outfile
			|| current_node->type.here_doc || current_node->type.append))
			len++;
		current_node = current_node->next;
	}
	return (len);
}

void	copy_command(t_cmd *cmd, t_shell *shell)
{
	int		y;
	t_arg	*current_node;

	y = 0;
	current_node = shell->arg;
	while (current_node && !current_node->token.pipe)
	{
		if (!(current_node->token.t_infile || current_node->token.t_outfile
			|| current_node->token.t_here_doc || current_node->token.t_append
			|| current_node->type.infile || current_node->type.outfile
			|| current_node->type.here_doc || current_node->type.append))
		{
			cmd->matrix[y] = ft_strdup(current_node->str);
			y++;
		}
		current_node = current_node->next;
	}
	cmd->matrix[y] = NULL;
	if (current_node && current_node->token.pipe && current_node->next)
		current_node = current_node->next;
	shell->arg = current_node;
}

void	copy_redir(t_redir_list *redir, t_shell *shell)
{
	t_arg	*current_node;

	current_node = shell->arg;
	while (current_node && !current_node->token.pipe)
	{
		
		if ((current_node->type.infile || current_node->type.outfile
			|| current_node->type.here_doc || current_node->type.append))
		{
			if (current_node->type.infile)
				redir->type.infile = true;
			else if (current_node->type.outfile)
				redir->type.outfile = true;
			else if (current_node->type.here_doc)
				redir->type.here_doc = true;
			else if (current_node->type.append)
				redir->type.append = true;
			redir->fd_name = ft_strdup(current_node->str);
			redir = redir->next;
		}
		current_node = current_node->next;
	}
	if (current_node && current_node->token.pipe && current_node->next)
		current_node = current_node->next;
	shell->arg = current_node;
}