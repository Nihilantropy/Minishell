/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redir_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:16:23 by crea              #+#    #+#             */
/*   Updated: 2024/09/23 15:02:35 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	open_heredoc(t_redir_list *current_node)
{
	int	read_file;

	read_file = open(current_node->here_doc->tmp_file_name, O_RDONLY);
	if (read_file == -1)
		ft_exit_error(ERR_HERE_DOC);
	if (dup2(read_file, STDIN_FILENO) == -1)
		perror("dup2 here_doc");
	close(read_file);
}

void	open_infile(t_redir_list *current_node)
{
	int	read_file;

	read_file = open(current_node->fd_name, O_RDONLY, 0777);
	if (read_file == -1)
		ft_exit_error(ERR_READ_FILE);
	if (dup2(read_file, STDIN_FILENO) == -1)
		perror("dup2 infile");
	close(read_file);
}

void	open_outfile(t_redir_list *current_node)
{
	int	write_file;

	write_file = open(current_node->fd_name,
			O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (write_file == -1)
		ft_exit_error(ERR_WRITE_FILE);
	if (dup2(write_file, STDOUT_FILENO) == -1)
		perror("dup2 outfile");
	close(write_file);
}

void	open_append(t_redir_list *current_node)
{
	int	write_file;

	write_file = open(current_node->fd_name,
			O_WRONLY | O_CREAT | O_APPEND, 0600);
	if (write_file == -1)
		ft_exit_error(ERR_WRITE_FILE);
	if (dup2(write_file, STDOUT_FILENO) == -1)
		perror("dup2 perror");
	close(write_file);
}
