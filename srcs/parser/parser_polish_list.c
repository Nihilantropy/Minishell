#include "../../include/minishell.h"

static void	set_node_index(t_arg *current_node);
static void	set_fd_flag(t_arg *current_node);
static void	count_pipes(t_shell *shell, t_arg *current_node);

/*	polish list:
**	After the list is fully created, we have to set thing up:
**	1) Handle the env variables 
**	2) Setting the correct index of the node 
**	3) Find if the node contains a redirection 
**	4) Count the number of pipes in all the command line
*/
void	polish_list(t_shell *shell, t_arg *arg)
{
	t_arg	*current_node;

	if (!arg)
		return ;
	current_node = arg;
	while (current_node)
	{
		if ((current_node->quote.none_q || current_node->quote.double_q)
			&& current_node->str && ft_strchr(current_node->str, '$'))
			handle_env_var(shell, current_node);
		set_node_index(current_node);
		set_fd_flag(current_node);
		count_pipes(shell, current_node);
		current_node = current_node->next;
	}
}

/*	set node index:
**	Setting up the index for each node of the list.
*/
static void	set_node_index(t_arg *current_node)
{
	if (current_node->prev == current_node)
		current_node->index = 1;
	else
		current_node->index = current_node->prev->index + 1;
}

/*	set fd flag:
**	Setting up the node flag, corrisponding to the 
**	previous token flag.
*/
static void	set_fd_flag(t_arg *current_node)
{
	t_arg	*next_node;

	next_node = current_node->next;
	if (current_node && next_node)
	{
		if (current_node->token.t_infile && next_node)
			next_node->type.infile = true;
		else if (current_node->token.t_outfile && next_node)
			next_node->type.outfile = true;
		else if (current_node->token.t_here_doc && next_node)
			next_node->type.here_doc = true;
		else if (current_node->token.t_append && next_node)
			next_node->type.append = true;
		if (current_node->token.t_infile || current_node->token.t_outfile
			|| current_node->token.t_here_doc || current_node->token.t_append)
			next_node->type.is_redir = true;
	}
}

/*	count pipes:
**	count the number of pipe token. 
*/
static void	count_pipes(t_shell *shell, t_arg *current_node)
{
	if (current_node->token.pipe)
		shell->pipes_nbr++;
}
