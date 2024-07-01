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
	printf("cmd length is: %d\n", len);
	printf("current node pointer is: %p\n", current_node);
	return (len);
}

void	copy_command(t_cmd *cmd, t_arg **arg)
{
	int		y;
	t_arg	*current_node;

	y = 0;
	current_node = *arg;
	while (current_node && !current_node->token.pipe)
	{
		if (!(current_node->token.t_infile || current_node->token.t_outfile
			|| current_node->token.t_here_doc || current_node->token.t_append
			|| current_node->type.infile || current_node->type.outfile
			|| current_node->type.here_doc || current_node->type.append))
		{
			cmd->matrix[y] = ft_strdup(current_node->str);
			printf("matrix at index [%d] is: %s\n", y, cmd->matrix[y]);
			printf("current node str is: %s\n", current_node->str);
			y++;
		}
		current_node = current_node->next;
	}
	cmd->matrix[y] = NULL;
	*arg = current_node;
}

void	copy_redir(t_redir_list *redir, t_arg **arg)
{
	t_arg	*current_node;

	current_node = *arg;
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
		}
		current_node = current_node->next;
	}
	*arg = current_node;
}