#include "../../include/minishell.h"

static void	handle_here_doc(t_redir_list *current_node);

void	reset_redir(t_shell *shell, int stdin_copy, int stdout_copy)
{
	t_cmd			*current_cmd_node;
	t_redir_list	*current_redir_node;

	current_cmd_node = shell->cmd;
	while (current_cmd_node)
	{
		current_redir_node = current_cmd_node->redir;
		while (current_redir_node)
		{
			if (current_redir_node->type.here_doc)
			{
				if (!access(current_redir_node->here_doc->tmp_file_name, F_OK))
					unlink(current_redir_node->here_doc->tmp_file_name);
			}
			current_redir_node = current_redir_node->next;
		}
		current_cmd_node = current_cmd_node->next;
	}
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
		if (current_node->type.here_doc)
			handle_here_doc(current_node);
		current_node = current_node->next;
	}
	current_node = redir;
	while (current_node)
	{
		if (current_node->type.infile)
		{
			read_file = open(current_node->fd_name, O_RDONLY, 0777);
			if (read_file == -1)
				ft_exit_error(ERR_READ_FILE);
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
				ft_exit_error(ERR_WRITE_FILE);
			dup2(write_file, STDOUT_FILENO);
			close(write_file);
		}
		if (current_node->type.append)
		{
			write_file = open(current_node->fd_name, O_WRONLY | O_CREAT | O_APPEND, 0600);
			if (write_file == -1)
				ft_exit_error(ERR_WRITE_FILE);
			dup2(write_file, STDOUT_FILENO);
			close(write_file);
		}
		current_node = current_node->next;
	}
}

static void	handle_here_doc(t_redir_list *current_node)
{
	int		stdin_copy;
	int		here_doc;
	char	*here_doc_fd_name;
	char	*line;
	static int i = 1;

	stdin_copy = dup(STDIN_FILENO);
	here_doc_fd_name = current_node->here_doc->tmp_file_name;
	here_doc = open(here_doc_fd_name, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (here_doc == -1)
		ft_exit_error(ERR_HERE_DOC);
	printf("EVVIVA giro %d!\n", i++);
	while (1)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			printf("line is %p\n", line);
			return ;
		}
		printf("EVVIVA!\n");
		if (!ft_strncmp(line, current_node->fd_name, ft_strlen(current_node->fd_name)))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, here_doc);
		free(line);
	}
	close(here_doc);
	here_doc = open(here_doc_fd_name, O_RDONLY);
	if (here_doc == -1)
		ft_exit_error(ERR_HERE_DOC);
	dup2(here_doc, STDIN_FILENO);
	close(here_doc);
}