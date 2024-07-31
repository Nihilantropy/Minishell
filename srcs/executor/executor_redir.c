#include "../../include/minishell.h"

static void	handle_here_doc(t_shell *shell, t_redir_list *current_node);
static void	open_here_doc_r(int here_doc, char *here_doc_fd_name);

/*
	1) Loop all the redir list. Find each here_doc node to unset the file
	2) Reset the STDIN and the STDOUT to the default one
	3) Close the old file descriptor
*/
void	reset_redir(t_shell *shell)
{
	if (dup2(shell->stdin_copy, STDIN_FILENO) == -1)
		perror("dup2 stdin_copy");
	if (dup2(shell->stdout_copy, STDOUT_FILENO) == -1)
		perror("dup2 stdout_copy");
	close(shell->stdin_copy);
	close(shell->stdout_copy);
}

/*
	1) Loop all the redir list to find the here_doc nodes
	2) Loop all the redir list to find the infile nodes
*/
void	redir_input(t_shell *shell, t_redir_list *redir)
{
	t_redir_list	*current_node;
	int				read_file;

	current_node = redir;
	while (current_node)
	{
		if (current_node->type.here_doc)
			handle_here_doc(shell, current_node);
		else if (current_node->type.infile)
		{
			read_file = open(current_node->fd_name, O_RDONLY, 0777);
			if (read_file == -1)
				ft_exit_error(ERR_READ_FILE);
			if (dup2(read_file, STDIN_FILENO) == -1)
				perror("dup2 infile");
			close(read_file);
		}
		current_node = current_node->next;
	}
}

/*
	1) Loop all the redir list to find either the outfile node or the append node
*/
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
				ft_exit_error(ERR_WRITE_FILE);
            if (dup2(write_file, STDOUT_FILENO) == -1)
                perror("dup2 outfile");
			close(write_file);
		}
		if (current_node->type.append)
		{
			write_file = open(current_node->fd_name, O_WRONLY | O_CREAT | O_APPEND, 0600);
			if (write_file == -1)
				ft_exit_error(ERR_WRITE_FILE);
            if (dup2(write_file, STDOUT_FILENO) == -1)
				perror("dup2 append");
			close(write_file);
		}
		current_node = current_node->next;
	}
}

/*
	1) Open the here_doc_*.temp in write mode
	2) Write on the here_doc_*.tmp untill the limiter is called
	3) Close the here_doc_*.tmp
	4) Reopen the here_doc_*.tmp in read mode
*/
static void	handle_here_doc(t_shell *shell, t_redir_list *current_node)
{
	int		here_doc;
	char	*line;

	here_doc = open(current_node->here_doc->tmp_file_name, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (here_doc == -1)
		ft_exit_error(ERR_HERE_DOC);
	while (1)
	{
		ft_putstr_fd("> ", shell->stdin_copy);
		line = get_next_line(shell->stdin_copy);
		if (!line)
		{
			perror("line (nil)");
			return ;
		}
		if (!ft_strncmp(line, current_node->fd_name, ft_strlen(current_node->fd_name)))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, here_doc);
		free(line);
	}
	close(here_doc);
	open_here_doc_r(here_doc, current_node->here_doc->tmp_file_name);
}

static void	open_here_doc_r(int here_doc, char *here_doc_fd_name)
{
	here_doc = open(here_doc_fd_name, O_RDONLY);
	if (here_doc == -1)
		ft_exit_error(ERR_HERE_DOC);
	if (dup2(here_doc, STDIN_FILENO) == -1)
		perror("dup2 here_doc");
	close(here_doc);
}