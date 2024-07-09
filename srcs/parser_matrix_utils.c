#include "../include/minishell.h"

static void	set_node_type(t_redir_list *redir, t_arg *current_node);

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
			len++;
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

/*
	1) Copy the redirections untill the end or the pipe and set the
		corrisponding type
	2) If the current node is a pipe, move the node to the next one
	3) Move the head of the arg list to the current node
*/
void	copy_redir(t_redir_list *redir, t_shell *shell)
{
	t_arg	*current_node;

	current_node = shell->arg;
	while (current_node && !current_node->token.pipe)
	{
		
		if (current_node->type.is_redir)
		{
			set_node_type(redir, current_node);
			redir->fd_name = ft_strdup(current_node->str);
			redir = redir->next;
		}
		current_node = current_node->next;
	}
	if (current_node && current_node->token.pipe && current_node->next)
		current_node = current_node->next;
	shell->arg = current_node;
}

static void	set_node_type(t_redir_list *redir, t_arg *current_node)
{
	if (current_node->type.infile)
		redir->type.infile = true;
	else if (current_node->type.outfile)
		redir->type.outfile = true;
	else if (current_node->type.here_doc)
		redir->type.here_doc = true;
	else if (current_node->type.append)
		redir->type.append = true;
	redir->type.is_redir = true;
}
