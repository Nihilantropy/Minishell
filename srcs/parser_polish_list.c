#include "../include/minishell.h"

static void	set_node_index(t_arg *current_node);
static void	set_fd_flag(t_arg *current_node);
static void	count_pipes(t_shell *shell, t_arg *current_node);
static void	check_token_index(t_arg *arg);

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

	if (!arg)
		return ;
	current_node = arg;
	check_token_index(current_node);
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

/*
	Check if the pipe token is at the start or at
	the end of the list. If so, we print an error message
	and start a new prompt.
*/
static void	check_token_index(t_arg *first_node)
{
	t_arg	*last_node;

	if (!first_node)
		return ;
	last_node = find_last_node(first_node);
	if (first_node->token.pipe)
	{
		rl_replace_line(ERR_PIPE_FIRST_INDEX, ft_strlen(ERR_PIPE_FIRST_INDEX));
		rl_on_new_line();
		rl_redisplay();
		printf("\nminishell$ ");
	}
	else if (last_node->token.pipe)
	{
		rl_replace_line(ERR_PIPE_LAST_INDEX, ft_strlen(ERR_PIPE_LAST_INDEX));
		rl_on_new_line();
		rl_redisplay();
		printf("\nminishell$ ");
	}
	return ;
}

/*
	Setting up the index for each node of the list
*/
static void	set_node_index(t_arg *current_node)
{
	if (current_node->prev == current_node)
		current_node->index = 1;
	else
		current_node->index = current_node->prev->index + 1;
}

/*
	Setting up the node flag, corrisponding to the 
	previous token flag.
*/
static void	set_fd_flag(t_arg *current_node)
{
	if (current_node && current_node->next)
	{
		if (current_node->token.t_infile && current_node->next)
			current_node->next->type.infile = true;
		else if (current_node->token.t_outfile && current_node->next)
			current_node->next->type.outfile = true;
		else if (current_node->token.t_here_doc && current_node->next)
			current_node->next->type.here_doc = true;
		else if (current_node->token.t_append && current_node->next)
			current_node->next->type.append = true;
		if (current_node->token.t_infile || current_node->token.t_outfile
			|| current_node->token.t_here_doc || current_node->token.t_append)
			current_node->next->type.is_redir = true;
	}
}

/*
	Count the number of pipe token 
*/
static void	count_pipes(t_shell *shell, t_arg *current_node)
{
	if (current_node->token.pipe)
		shell->pipes_nbr++;
}
