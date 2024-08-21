#include "../../include/minishell.h"

static int	handle_heredoc_eof(char *line, t_redir_list *current_node);
static void	open_heredoc_w(t_redir_list *current_node);

/* handle heredoc:
	1) Open the here_doc_*.temp in write mode
	2) Write on the here_doc_*.tmp untill the limiter is called
	3) Close the here_doc_*.tmp
*/
void	handle_heredoc(t_shell *shell)
{
	t_cmd			*current_cmd_node;
	t_redir_list	*current_redir_node;

	current_cmd_node = shell->cmd;
	while (current_cmd_node)
	{
		current_redir_node = current_cmd_node->redir;
		while (current_redir_node)
		{
			open_heredoc_w(current_redir_node);
			current_redir_node = current_redir_node->next;
		}
		current_cmd_node = current_cmd_node->next;
	}
}

static void	open_heredoc_w(t_redir_list *current_node)
{
	int		here_doc;
	char	*line;

	here_doc = open(current_node->here_doc->tmp_file_name,
						O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (here_doc == -1)
		ft_exit_error(ERR_HERE_DOC);
	while (1)
	{
		ft_putstr_fd("> ", STDIN_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (handle_heredoc_eof(line, current_node))
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
}

static int	handle_heredoc_eof(char *line, t_redir_list *current_node)
{
	(void)current_node;
	if (!line)
	{
		ft_putstr_fd("\n-minishell: warning: here_document closed.\n", 2);
		return (1);
	}
	return (0);
}
