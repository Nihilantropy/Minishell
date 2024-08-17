#include "../../include/minishell.h"

int	handle_here_doc_sigterm(char *line, t_redir_list *current_node)
{
	(void)current_node;
	if (!line)
	{
		ft_putstr_fd("\n-minishell: warning: here_document closed.\n", 2);
		return (1);
	}
	return (0);
}

void	open_here_doc_r(int here_doc, char *here_doc_fd_name)
{
	here_doc = open(here_doc_fd_name, O_RDONLY);
	if (here_doc == -1)
		ft_exit_error(ERR_HERE_DOC);
	if (dup2(here_doc, STDIN_FILENO) == -1)
		perror("dup2 here_doc");
	close(here_doc);
}