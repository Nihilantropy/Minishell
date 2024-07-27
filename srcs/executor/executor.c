#include "../../include/minishell.h"

static void	handle_redir(t_redir_list *redir);
static void	redir_input(t_redir_list *redir);
static void	redir_output(t_redir_list *redir);

void	executor(t_shell *shell)
{
	t_cmd	*current_node;

	current_node = shell->cmd;
	while (current_node)
	{
		handle_redir(current_node->redir);
		if (current_node->builtin.is_builtin)
			handle_builtin(shell, current_node);
		else
			printf("Current command not a builtin. Execute normally.\n");
		current_node = current_node->next;
	}
}

static void	handle_redir(t_redir_list *redir)
{
	//redir_here_doc(redir);
	redir_input(redir);
	redir_output(redir);
}
/*
static void	redir_here_doc(t_redir_list *redir)
{
	t_redir_list	*current_node;
	int				here_doc;
	char			*line;

	current_node = redir;
	while (current_node)
	{
		if (current_node->type.here_doc)
		{
			here_doc = open(".here_doc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0600);
			if (here_doc == -1)
				ft_exit_error("ERRORE here_doc\n");
			while (1)
			{
				ft_putstr_fd("> ", STDOUT_FILENO);
				line = get_next_line(STDIN_FILENO);
				if (!line)
					return ;
				ft_putstr_fd(line, here_doc);
				if (!ft_strcmp(ft_strtrim(line, " \t\n\r\v"), current_node->fd_name))
					break ;
				free(line);
			}
			if (line)
				free(line);
			dup2(here_doc, STDIN_FILENO);
		}
		current_node = current_node->next;
	}
}

*/
static void	redir_input(t_redir_list *redir)
{
	t_redir_list	*current_node;
	int				infile;

	current_node = redir;
	while (current_node)
	{
		if (current_node->type.infile)
		{
			infile = open(redir->fd_name, O_RDONLY, 0777);
			if (infile == -1)
				ft_exit_error("ERRORE di lettura\n");
			dup2(infile, STDIN_FILENO);
		}
		current_node = current_node->next;
	}
}

static void	redir_output(t_redir_list *redir)
{
	t_redir_list	*current_node;
	int				outfile;
	int				append;

	current_node = redir;
	while (current_node)
	{
		if (current_node->type.outfile)
		{
			outfile = open(redir->fd_name, O_WRONLY | O_CREAT | O_TRUNC, 0600);
			if (outfile == -1)
				ft_exit_error("ERRORE\n");
			dup2(outfile, STDOUT_FILENO);
		}
		else if (current_node->type.append)
		{
			append = open(redir->fd_name, O_WRONLY | O_CREAT | O_APPEND, 0600);
			if (append == -1)
				ft_exit_error("ERRORE\n");
			dup2(append, STDOUT_FILENO);
		}
		current_node = current_node->next;
	}
}
