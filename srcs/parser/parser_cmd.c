#include "../../include/minishell.h"

static void	init_cmd_node(t_shell *shell, int i);
static void	build_cmd_nodes(t_shell *shell);
static void	build_cmd_matrix(t_cmd *cmd, t_shell *shell);

/*	parse matrix:
		1) Initialize the nodes based on the number of pipes
		2) Build the list with the commands and the redirections
*/
void	parse_matrix(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < (shell->pipes_nbr + 1))
	{
		init_cmd_node(shell, i);
		i++;
	}
	build_cmd_nodes(shell);
}

/*	init cmd node:
		initializing the command node and appending the node to the list.
*/
static void	init_cmd_node(t_shell *shell, int i)
{
	t_cmd	*new_node;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_node)
		ft_exit_error(ERR_ALLOC_NEW_NODE);
	new_node->index = i + 1;
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

/*	build cmd nodes:
	1) Saving the real head of the arg list
	2) Inside the loop, make the current head move to the node
		after the pipe to build the command matrix
	3) Need to reset the head on the start of the list or at the last pipe
	4) The head will move again while building the redirection list, and it will
		restart one node after the last pipe
	5) Reset the arg head to point to it's real head, so we can free the list
*/
static void	build_cmd_nodes(t_shell *shell)
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
}

/*	build cmd matrix:
		1) Search how many space we need for the command and the eventual flags,
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
