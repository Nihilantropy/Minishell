/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:44:49 by crea              #+#    #+#             */
/*   Updated: 2024/09/23 13:44:50 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	init_redir_node(t_redir_list **redir);
static void	copy_redir(t_redir_list *redir, t_shell *shell);
static void	create_heredoc_list(t_arg *current_node, t_redir_list *redir, int here_doc_index);

/*	build redir list:
**	1) Build all the necessary nodes for the redirection list, each inside the
**		command node
**	2) Copy the redirection file name inside the node, with the corrisponding types
*/
void	build_redir_list(t_cmd *cmd, t_shell *shell)
{
	t_arg	*current_node;

	if (!shell->arg)
		return ;
	current_node = shell->arg;
	while (current_node && !current_node->token.pipe)
	{
		if (current_node->type.is_redir)
			init_redir_node(&cmd->redir);
		current_node = current_node->next;
	}
	copy_redir(cmd->redir, shell);
}

/*	init redir node:
**	Initializing the redirection node and appending the node to the list.
*/
static void	init_redir_node(t_redir_list **redir)
{
	t_redir_list	*new_node;

	new_node = malloc(sizeof(t_redir_list));
	if (!new_node)
		ft_exit_error(ERR_ALLOC_REDIR);
	new_node->fd_name = NULL;
	new_node->here_doc = NULL;
	new_node->type.is_redir = false;
	new_node->type.infile = false;
	new_node->type.outfile = false;
	new_node->type.here_doc = false;
	new_node->type.append = false;
	append_redir_node(redir, new_node);
}

/*	copy redir:
**	1) Copy the redirections untill the end or the pipe and set the
**		corrisponding type
**	2) If the current node is a pipe, move the node to the next one
**	3) Move the head of the arg list to the current node
*/
static void	copy_redir(t_redir_list *redir, t_shell *shell)
{
	t_arg	*current_node;
	int		here_doc_index;

	here_doc_index = 1;
	current_node = shell->arg;
	while (current_node && !current_node->token.pipe)
	{
		
		if (current_node->type.is_redir)
		{
			set_node_type(redir, current_node);
			redir->fd_name = ft_strdup(current_node->str);
			if (redir->type.here_doc)
				create_heredoc_list(current_node, redir, here_doc_index++);
			redir = redir->next;
		}
		current_node = current_node->next;
	}
	if (current_node && current_node->token.pipe && current_node->next)
		current_node = current_node->next;
	shell->arg = current_node;
}

/*	create heredoc list:
**	Create a struct for the here_doc, saving the spiecific index
**	of the file, and the speicific name, based on the index.
**	Also check what type of quotetion the node has in order to
**	check the $VAR expantion.
*/
static void	create_heredoc_list(t_arg *current_node, t_redir_list *redir, int here_doc_index)
{
	char	*temp;
	char	*file_name;
	char	*index_str;

	redir->here_doc = malloc(sizeof(t_here_doc));
	if (!redir->here_doc)
		ft_exit_error(ERR_ALLOC_HERE_DOC);
	redir->here_doc->limiter = ft_strdup(redir->fd_name);
	redir->here_doc->index = here_doc_index;
	index_str = ft_itoa(here_doc_index);
	temp = ft_strjoin(index_str, ".tmp");
	free(index_str);
	file_name = ft_strjoin(".here_doc_", temp);
	free(temp);
	redir->here_doc->tmp_file_name = file_name;
	if (current_node->quote.none_q || current_node->quote.double_q)
		redir->here_doc->expand = true;
	else
		redir->here_doc->expand = false;
}
