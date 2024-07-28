#include "../../include/minishell.h"

void	reset_redir(int stdin_copy, int stdout_copy)
{
	dup2(stdin_copy, STDIN_FILENO);
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdin_copy);
	close(stdout_copy);
}

void	redir_input(t_redir_list *redir)
{
	t_redir_list	*current_node;
	int				read_file;

	current_node = redir;
	while (current_node)
	{
		if (current_node->type.infile)
		{
			read_file = open(current_node->fd_name, O_RDONLY, 0777);
			if (read_file == -1)
				ft_exit_error("ERRORE di lettura\n");
			dup2(read_file, STDIN_FILENO);
			close(read_file);
		}
		current_node = current_node->next;
	}
}

void	redir_output(t_redir_list *redir)
{
	t_redir_list	*current_node;
	int				write_file;

	current_node = redir;
	while (current_node)
	{
		if (current_node->type.outfile)
		{
			write_file = open(current_node->fd_name, O_WRONLY | O_CREAT | O_TRUNC, 0600);
			if (write_file == -1)
				ft_exit_error("ERRORE\n");
			dup2(write_file, STDOUT_FILENO);
			close(write_file);
		}
		if (current_node->type.append)
		{
			write_file = open(current_node->fd_name, O_WRONLY | O_CREAT | O_APPEND, 0600);
			if (write_file == -1)
				ft_exit_error("ERRORE\n");
			dup2(write_file, STDOUT_FILENO);
			close(write_file);
		}
		current_node = current_node->next;
	}
}
