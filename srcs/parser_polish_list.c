#include "../include/minishell.h"

static void	set_node_index(t_arg *current_node);
static void	set_fd_flag(t_arg *current_node);
static void	count_pipes(t_shell *shell, t_arg *current_node);

/* 
	After the list is fully created, we have to set thing up.
	1) Handle the env variables 
	2) Setting the correct index of the node 
	3) Find if the node contains a redirection 
	4) Count the nubmer of pipes in all the command line 
*/
void	polish_list(t_shell *shell, t_arg *arg)
{
	t_arg	*current_node;

	current_node = arg;
	if (!current_node)
		return ;
	while (current_node)
	{
		if ((current_node->quote.NONE || current_node->quote.DOUBLE)
			&& current_node->str && ft_strchr(current_node->str, '$'))
			handle_env_var(shell, current_node);
		set_node_index(current_node);
		set_fd_flag(current_node);
		count_pipes(shell, current_node);
		current_node = current_node->next;
	}
}

static void	set_node_index(t_arg *current_node)
{
	if (current_node->prev == current_node)
		current_node->index = 1;
	else
		current_node->index = current_node->prev->index + 1;
}

static void	set_fd_flag(t_arg *current_node)
{
	if (current_node->token.t_infile && current_node->next)
		current_node->next->token.infile = true;
	else if (current_node->token.t_outfile && current_node->next)
		current_node->next->token.outfile = true;
	else if (current_node->token.t_here_doc && current_node->next)
		current_node->next->token.here_doc = true;
	else if (current_node->token.t_append && current_node->next)
		current_node->next->token.append = true;
}

static void	count_pipes(t_shell *shell, t_arg *current_node)
{
	if (current_node->token.pipe)
		shell->pipes_nbr++;
}
