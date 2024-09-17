#include "../../include/minishell.h"

/*	free all redir list
**	Loop trough every cmd node to free each redir list
*/
void	free_all_redir_list(t_cmd *cmd)
{
	t_cmd 			*current_cmd_node;

	current_cmd_node = cmd;
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

	current = *redir;
	if (!current)
		return ;
	while (current)
	{
		next_node = current->next;
		if (current->fd_name)
			free(current->fd_name);
		if (current->here_doc)
		{
			if (!access(current->here_doc->tmp_file_name, F_OK))
					unlink(current->here_doc->tmp_file_name);
			free(current->here_doc->limiter);
			free(current->here_doc->tmp_file_name);
			free(current->here_doc);
			current->here_doc = NULL;
		}
		free(current);
		current = next_node;
	}
	*redir = NULL;
}

/*
void	print_redir_list(t_cmd *cmd)
{
	t_redir_list	*redir;

	if (!cmd)
		return ;
	while (cmd)
	{
		redir = cmd->redir;
		while (redir)
		{
			ft_putnl();
			printf("str: %s\n", redir->fd_name);
			if (redir->type.is_redir)
				printf("is a redirection\n");
			if (redir->type.infile)
				printf("type = infile\n");
			else if (redir->type.outfile)
				printf("type = outfile\n");
			else if (redir->type.here_doc)
				printf("type = here_doc\n");
			else if (redir->type.append)
				printf("redir = append\n");
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}
*/