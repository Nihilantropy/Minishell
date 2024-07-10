#include "../include/minishell.h"

static void	init_cmd_node(t_shell *shell);
static void	init_redir_node(t_redir_list **redir);
static void	build_nodes(t_shell *shell);
static void	build_cmd_matrix(t_cmd *cmd, t_shell *shell);
static void	build_redir_list(t_cmd *cmd, t_shell *shell);

/*
	1) Initialize the nodes based on the number of pipes
	2) Build the list with the commands and the redirections
*/
void	parse_matrix(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < (shell->pipes_nbr + 1))
	{
		init_cmd_node(shell);
		i++;
	}
	build_nodes(shell);
}

/*
	Initializing the command node and appending the node to the list
*/
static void	init_cmd_node(t_shell *shell)
{
	t_cmd	*new_node;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_node)
		ft_exit_error(ERR_ALLOC_NEW_NODE);
	new_node->matrix = NULL;
	new_node->redir = NULL;
	new_node->builtin.is_builtin = false;
	new_node->builtin.cd = false;
	new_node->builtin.echo = false;
	new_node->builtin.pwd = false;
	new_node->builtin.export = false;
	new_node->builtin.unset = false;
	new_node->builtin.env = false;
	new_node->builtin.exit = false;
	append_cmd_node(&shell->cmd, new_node);
}

/*
	1) Saving the real head of the arg list
	2) Inside the loop, make the current head move to the node
		after the pipe to build the command matrix
	3) Need to reset the head on the start of the list or at the last pipe
	4) The head will move again to while building the redirection list, and it will
		restart one node after the last pipe
	5) Reset the arg head to point to it's real head, so we can free the list
*/
static void	build_nodes(t_shell *shell)
{
	t_cmd	*current_node;
	t_arg	*current_head;
	t_arg	*real_head;

	if (!shell->cmd || !shell->arg)
		return ;
	real_head = shell->arg;
	current_node = shell->cmd;
	while (current_node)
	{
		current_head = shell->arg;
		build_cmd_matrix(current_node, shell);
		shell->arg = current_head;
		build_redir_list(current_node, shell);
		current_node = current_node->next;
	}
	shell->arg = real_head;
	print_cmd_list(shell->cmd);
	print_redir_list(shell->cmd);
}

/*
	1) Search how many spaces we need for the command and the eventual flags,
		skipping the redirection nodes
	2) Copy the commands inside the matrix cells, moving the arg head meanwhile
*/
static void	build_cmd_matrix(t_cmd *cmd, t_shell *shell)
{
	int	len;

	len = len_to_pipe_cmd(shell->arg);
	cmd->matrix = malloc(sizeof(char *) * (len + 1));
	if (!cmd->matrix)
		ft_exit_error(ERR_ALLOC_MATRIX);
	copy_command(cmd, shell);
	check_builtin(cmd);
}

/*
	1) Build all the necessary nodes for the redirection list, each inside the
		command node
	2) Copy the redirection file name inside the node, with the corrisponding types
*/
static void	build_redir_list(t_cmd *cmd, t_shell *shell)
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

/*
	Initializing the redirection node and appending the node to the list
*/
static void	init_redir_node(t_redir_list **redir)
{
	t_redir_list	*new_node;

	new_node = malloc(sizeof(t_redir_list));
	if (!new_node)
		ft_exit_error(ERR_ALLOC_REDIR);
	new_node->fd_name = NULL;
	new_node->type.is_redir = false;
	new_node->type.infile = false;
	new_node->type.outfile = false;
	new_node->type.here_doc = false;
	new_node->type.append = false;
	append_redir_node(redir, new_node);
}
