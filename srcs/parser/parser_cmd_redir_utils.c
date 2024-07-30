#include "../../include/minishell.h"

static t_redir_list	*find_last_redir_node(t_redir_list *redir);

/*
	Set the corrisponding redirection type
*/
void	set_node_type(t_redir_list *redir, t_arg *current_node)
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

void	append_redir_node(t_redir_list **redir, t_redir_list *new_node)
{
	t_redir_list	*last_node;

	if (!*redir)
	{
		*redir = new_node;
		new_node->prev = new_node;
	}
	else
	{
		last_node = find_last_redir_node(*redir);
		last_node->next = new_node;
		new_node->prev = last_node;
		(*redir)->prev = new_node;
	}
	new_node->next = NULL;
}

static t_redir_list	*find_last_redir_node(t_redir_list *redir)
{
	if (!redir)
		return (NULL);
	while (redir->next)
		redir = redir->next;
	return (redir);
}

/*
	Loop trough every cmd node to free each redir list
*/
void	free_all_redir_list(t_cmd *cmd)
{
	t_cmd 			*current_cmd_node;

	current_cmd_node = cmd;
	if (!current_cmd_node)
		return ;
	while (current_cmd_node)
	{
		free_redir_list(&current_cmd_node->redir);
		current_cmd_node = current_cmd_node->next;
	}
}

void	free_redir_list(t_redir_list **redir)
{
	t_redir_list	*current;
	t_redir_list	*next_node;

	if (!*redir)
		return ;
	current = *redir;
	while (current)
	{
		next_node = current->next;
		if (current->fd_name)
			free(current->fd_name);
		if (current->here_doc)
		{
			free(current->here_doc->limiter);
			free(current->here_doc->tmp_file_name);
			free(current->here_doc);
		}
		free(current);
		current = next_node;
	}
	*redir = NULL;
}
