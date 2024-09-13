#include "../../include/minishell.h"

static int	handle_heredoc_eof(char *line);
static void	open_heredoc_w(t_shell *shell, t_redir_list *current_node);
static int	write_heredoc(t_shell *shell, t_redir_list *current_node, int here_doc);
static char	*handle_heredoc_env_var(t_shell *shell, char *line);

/*	handle heredoc:
**	Loop all the command list and all the redirection lists to
**	open the here document in write mode.
*/
void	handle_heredoc(t_shell *shell)
{
	t_cmd			*current_cmd_node;
	t_redir_list	*current_redir_node;
	pid_t			pid;
	int				status;

	current_cmd_node = shell->cmd;
	pid = fork();
	if (pid == -1)
		ft_exit_error(ERR_FORK);
	if (pid == 0)
	{
		sigint_handler_heredoc();
		while (current_cmd_node)
		{
			current_redir_node = current_cmd_node->redir;
			while (current_redir_node)
			{
				if (current_redir_node->here_doc)
					open_heredoc_w(shell, current_redir_node);
				current_redir_node = current_redir_node->next;
			}
			current_cmd_node = current_cmd_node->next;
		}
		exit(EXIT_SUCCESS);
	}
	wait(&status);
	g_exit_status = handle_exit_status(status);
}

/*	open heredoc w (write mode):
**	open the heredoc temp file and start the loop
**	until <<delimiter>> is found or 'eof' is found.
*/
static void	open_heredoc_w(t_shell *shell, t_redir_list *current_node)
{
	int		here_doc;

	here_doc = open(current_node->here_doc->tmp_file_name,
						O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (here_doc == -1)
		ft_exit_error(ERR_HERE_DOC);
	while (1)
	{
		if (write_heredoc(shell, current_node, here_doc) == 1)
			break ;
	}
	close(here_doc);
}

/*	write heredoc:
**	read the line from STDIN utill \n is found, then parse the
**	line if the node is a none-quote or double-quote node, to expand
**	the env $VAR.
**	write the line on the heredoc file descriptor.
*/
static int	write_heredoc(t_shell *shell, t_redir_list *current_node, int here_doc)
{
	char	*line;
	char	*parsed_line;

	ft_putstr_fd("> ", STDIN_FILENO);
	line = get_next_line(STDIN_FILENO);
	if (handle_heredoc_eof(line))
		return (1);
	if (current_node->here_doc->expand == true)
		parsed_line = handle_heredoc_env_var(shell, line);
	else
		parsed_line = line;
	if (!ft_strncmp(parsed_line, current_node->fd_name, ft_strlen(current_node->fd_name)) &&
		ft_strlen(current_node->fd_name) == (ft_strlen(parsed_line) - 1))
	{
		free(parsed_line);
		return (1);
	}
	ft_putstr_fd(parsed_line, here_doc);
	free(parsed_line);
	return (0);
}

/*	handle heredoc env var:
**	Function that loops to replace all $VAR
**	with the correct variables.
**	If the string is parsed, point at the new string
**	and restart the loop until all '$' are correctly parsed.
*/
static char	*handle_heredoc_env_var(t_shell *shell, char *line)
{
	int		i;
	char	*old_str;
	char	*new_str;

	i = 0;
	while (line[i])
	{
		if (line[i + 1] && line[i] == '$')
		{
			old_str = line;
			new_str = parse_env_var(shell, line);
			if (!new_str)
				break ;
			line = new_str;
			free(old_str);
			i = 0;
		}
		else
			i++;
	}
	return (line);
}

/*	handle heredoc eof:
**	if CTRL + D (EOF) is called, close the heredoc.
*/
static int	handle_heredoc_eof(char *line)
{
	if (!line)
	{
		ft_putstr_fd("\n-minishell: warning: here_document closed.\n", 2);
		return (1);
	}
	return (0);
}
