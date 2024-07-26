#include "../../include/minishell.h"

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

void	free_redir_list(t_cmd *cmd)
{
	t_redir_list	*current_redir_node;
	t_redir_list	*next_redir_node;
	t_cmd 			*current_cmd_node;

	current_cmd_node = cmd;
	while (current_cmd_node)
	{
		current_redir_node = current_cmd_node->redir;
		while (current_redir_node)
		{
			next_redir_node = current_redir_node->next;
			free(current_redir_node->fd_name);
			free(current_redir_node);
			current_redir_node = next_redir_node;
		}
		current_cmd_node->redir = NULL;
		current_cmd_node = current_cmd_node->next;
	}
}

void	print_cmd_list(t_cmd *cmd)
{
	if (!cmd)
		return ;
	while (cmd)
	{
		printf("\n------------------\n");
		print_matrix(cmd->matrix);
		cmd = cmd->next;
	}
}

void	free_cmd_list(t_cmd **cmd)
{
	t_cmd	*current;
	t_cmd	*next_node;

	if (!*cmd)
		return ;
	current = *cmd;
	while (current)
	{
		next_node = current->next;
		free_matrix(current->matrix);
		free(current);
		current = next_node;
	}
	*cmd = NULL;
}