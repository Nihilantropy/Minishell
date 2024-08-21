#include "../../include/minishell.h"

static int	handle_here_doc_sigterm(char *line, t_redir_list *current_node);
static void	open_here_doc_r(int here_doc, char *here_doc_fd_name);

/*
	1) Open the here_doc_*.temp in write mode
	2) Write on the here_doc_*.tmp untill the limiter is called
	3) Close the here_doc_*.tmp
	4) Reopen the here_doc_*.tmp in read mode
*/
void	handle_here_doc(t_shell *shell, t_redir_list *current_node)
{
	int		here_doc;
	char	*line;

	(void)shell;
	here_doc = open(current_node->here_doc->tmp_file_name, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (here_doc == -1)
		ft_exit_error(ERR_HERE_DOC);
	while (1)
	{
		ft_putstr_fd("> ", shell->stdin_copy);
		line = get_next_line(shell->stdin_copy);
		if (handle_here_doc_sigterm(line, current_node))
			break ;
		// TODO add the env var expander
		if (!ft_strncmp(line, current_node->fd_name, ft_strlen(current_node->fd_name)) &&
			ft_strlen(current_node->fd_name) == (ft_strlen(line) - 1))
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


static int	handle_here_doc_sigterm(char *line, t_redir_list *current_node)
{
	(void)current_node;
	if (!line)
	{
		ft_putstr_fd("\n-minishell: warning: here_document closed.\n", 2);
		return (1);
	}
	return (0);
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
