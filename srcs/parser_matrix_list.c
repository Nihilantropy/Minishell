#include "../include/minishell.h"

static t_cmd		*find_last_cmd_node(t_cmd *cmd);
static t_redir_list	*find_last_redir_node(t_redir_list *redir);

void	append_cmd_node(t_cmd **cmd, t_cmd *new_node)
{
	t_cmd	*last_node;

	if (!*cmd)
	{
		*cmd = new_node;
		new_node->prev = new_node;
	}
	else
	{
		last_node = find_last_cmd_node(*cmd);
		last_node->next = new_node;
		new_node->prev = last_node;
	}
	new_node->next = NULL;
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
	}
	new_node->next = NULL;
}

static t_cmd	*find_last_cmd_node(t_cmd *cmd)
{
	if (!cmd)
		return (NULL);
	while (cmd->next)
		cmd = cmd->next;
	return (cmd);
}

static t_redir_list	*find_last_redir_node(t_redir_list *redir)
{
	if (!redir)
		return (NULL);
	while (redir->next)
		redir = redir->next;
	return (redir);
}
