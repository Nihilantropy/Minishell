#include "../include/minishell.h"

int	len_to_pipe_cmd(t_arg *arg)
{
	int				len;
	static t_arg	*current_node;

	if (!arg)
		return (0);
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
	if (current_node->token.pipe && current_node->next)
		current_node = current_node->next;
	return (len);
}

void	copy_command(t_cmd *cmd, t_arg *arg)
{
	int				y;
	static t_arg	*current_node;

	if (!arg || !cmd)
		return ;
	y = 0;
	current_node = arg;
	while (current_node && !current_node->token.pipe)
	{
		if (!(current_node->token.t_infile || current_node->token.t_outfile
			|| current_node->token.t_here_doc || current_node->token.t_append
			|| current_node->type.infile || current_node->type.outfile
			|| current_node->type.here_doc || current_node->type.append))
			cmd->matrix[y++] = ft_strdup(current_node->str);
		current_node = current_node->next;
	}
	if (current_node->token.pipe && current_node->next)
		current_node = current_node->next;
}

void	copy_redir(t_redir_list *redir, t_arg *arg)
{
	static t_arg	*current_node;

	if (!redir || !arg)
		return ;
	current_node = arg;
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
			redir->fd_name = ft_strdup(arg->str);
		}
		current_node = current_node->next;
	}
	if (current_node->token.pipe && current_node->next)
		current_node = current_node->next;
}