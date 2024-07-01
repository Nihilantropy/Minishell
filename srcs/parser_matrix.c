#include "../include/minishell.h"


static void	init_cmd_node(t_cmd **cmd);
static void	init_redir_node(t_redir_list **redir);
static void	build_nodes(t_cmd **cmd, t_arg **arg);
static void	build_cmd_matrix(t_cmd *cmd, t_arg **arg);
static void	build_redir_list(t_cmd *cmd, t_arg **arg);

void	parse_matrix(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < (shell->pipes_nbr + 1))
	{
		init_cmd_node(&shell->cmd);
		printf("creating nodes %d\n", i);
		i++;
	}
	build_nodes(&shell->cmd, &shell->arg);
}


static void	init_cmd_node(t_cmd **cmd)
{
	t_cmd	*new_node;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_node)
		ft_exit_error(ERR_ALLOC_NEW_NODE);
	new_node->matrix = NULL;
	new_node->redir = NULL;
	append_cmd_node(cmd, new_node);
}

static void	build_cmd_matrix(t_cmd *cmd, t_arg **arg)
{
	int		len;

	len = len_to_pipe_cmd(*arg);
	cmd->matrix = malloc(sizeof(char *) * (len + 1));
	if (!cmd->matrix)
		ft_exit_error(ERR_ALLOC_MATRIX);
	copy_command(cmd, arg);
}

static void	build_redir_list(t_cmd *cmd, t_arg **arg)
{
	static t_arg	*current_node;

	if (!*arg)
		return ;
	current_node = *arg;
	while (current_node && !current_node->token.pipe)
	{
		if ((current_node->type.infile || current_node->type.outfile
			|| current_node->type.here_doc || current_node->type.append))
			init_redir_node(&cmd->redir);
		current_node = current_node->next;
	}
	copy_redir(cmd->redir, arg);
}

static void	init_redir_node(t_redir_list **redir)
{
	t_redir_list	*new_node;

	new_node = malloc(sizeof(t_redir_list));
	if (!new_node)
		ft_exit_error(ERR_REDIR_ALLOC);
	new_node->fd_name = NULL;
	new_node->type.infile = false;
	new_node->type.outfile = false;
	new_node->type.here_doc = false;
	new_node->type.append = false;
	append_redir_node(redir, new_node);
}

static void	build_nodes(t_cmd **cmd, t_arg **arg)
{
	t_cmd	*current_node;

	if (!*cmd || !*arg)
		return ;
	current_node = *cmd;
	while (current_node)
	{
		build_cmd_matrix(current_node, arg);
		build_redir_list(current_node, arg);
		current_node = current_node->next;
	}
	print_cmd_list(*cmd);
	print_redir_list((*cmd)->redir);
}























/*
static int	len_to_pipe(t_arg **current_head);
static void	init_matrix_z(t_shell *shell, char ***matrix);
static void	build_matrix(t_shell *shell, char ***matrix);


	1) Build the space for the matrixes: z index
		initializing all to NULL
	2) Build the space for the rows: y index
		initializing all to NULL
	3) Build the row of each matrix 
		TODO ----- with the right node ------

void	parse_matrix(t_shell *shell, t_arg *arg)
{
	int		z;
	int 	y;
	int		j;
	t_arg	**current_head;

	z = 0;
	j = 0;
	current_head = &arg;
	shell->matrix = (char ***)malloc(sizeof(char **) * (shell->pipes_nbr + 2));
	if (!shell->matrix)
		ft_exit_error(ERR_ALLOC_MATRIX);
	init_matrix_z(shell, shell->matrix);
	while (z <= shell->pipes_nbr)
	{
		y = len_to_pipe(current_head);
		shell->matrix[z] = (char **)malloc(sizeof(char *) * (y + 1));
		if (!shell->matrix[z])
			ft_exit_error(ERR_ALLOC_MATRIX);
		while (j <= y)
			shell->matrix[z][j++] = NULL;
		z++;
	}
	build_matrix(shell, shell->matrix);
	print_matrix(shell->matrix);
}

static void	init_matrix_z(t_shell *shell, char ***matrix)
{
	int	z;

	z = 0;
	while (z < shell->pipes_nbr + 2)
		matrix[z++] = NULL;
}

static int	len_to_pipe(t_arg **current_head)
{
	int			i;
	t_arg		*current_node;

	i = 0;
	current_node = *current_head;
	while (current_node && !current_node->token.pipe)
	{
		if (!current_node->token.t_infile
			&& !current_node->token.t_outfile
			&& !current_node->token.t_here_doc
			&& !current_node->token.t_append)
			i++;
		current_node = current_node->next;
	}
	if (current_node && current_node->next)
		*current_head = current_node->next;
	else
		*current_head = NULL;
	return (i);
}

static void	build_matrix(t_shell *shell, char ***matrix)
{
	int	z;
	int	y;
	int	j;
	t_arg	*current_node;
	t_arg	**current_head;

	z = 0;
	current_node = shell->arg;
	current_head = &shell->arg;
	printf("%s\n", current_node->str);
	while ((z <= shell->pipes_nbr + 2) && current_node)
	{
		y = 0;
		j = len_to_pipe(current_head);
		while ((y <= j) && current_node)
		{
			if (!current_node->token.t_infile
				&& !current_node->token.t_outfile
				&& !current_node->token.t_here_doc
				&& !current_node->token.t_append
				&& !current_node->token.pipe)
			{
				matrix[z][y] = ft_strdup(current_node->str);
				y++;
			}
			if (current_node->token.pipe)
				break;
			current_node = current_node->next;
		}
		z++;
		if (current_node && current_node->token.pipe)
			current_node = current_node->next;
	}
}
*/