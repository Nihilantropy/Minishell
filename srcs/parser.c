#include "../include/minishell.h"

static char	*create_quote_node(t_arg **arg, char *temp)
{
	char	quote;
	int		len;
	t_arg	*new_node;

	quote = *temp;
	new_node = init_new_node();
	len = arg_length(temp, new_node);
	new_node->str = (char *)malloc(len);
	if (!new_node->str)
		ft_exit_error(ERR_ALLOC_QUOTE_NODE);
	ft_strlcpy(new_node->str, temp + 1, len);
	if (quote == '\'')
		new_node->quote.SINGLE = true;
	else if (quote == '\"')
		new_node->quote.DOUBLE = true;
	append_node(arg, new_node);
	return (temp + len + 1);
}

static char	*create_token_node(t_arg **arg, char *temp)
{
	int		len;
	t_arg	*new_node;

	new_node = init_new_node();
	len = token_length(temp);
	new_node->str = (char *)malloc(len + 1);
	if (!new_node->str)
		ft_exit_error(ERR_ALLOC_TOKEN_NODE);
	ft_strlcpy(new_node->str, temp, len + 1);
	if (!ft_strcmp(new_node->str, "|"))
		new_node->token.pipe = true;
	else if (!ft_strcmp(new_node->str, "<"))
		new_node->token.t_infile = true;
	else if (!ft_strcmp(new_node->str, ">"))
		new_node->token.t_outfile = true;
	else if (!ft_strcmp(new_node->str, "<<"))
		new_node->token.t_here_doc = true;
	else if (!ft_strcmp(new_node->str, ">>"))
		new_node->token.t_append = true;
	new_node->token.is_token = true;
	new_node->quote.NONE = true;
	append_node(arg, new_node);
	return (temp + len);
}

static char	*create_new_node(t_arg **arg, char *temp)
{
	int		len;
	t_arg	*new_node;

	new_node = init_new_node();
	len = arg_length(temp, new_node);
	new_node->str = (char *)malloc(len + 1);
	if (!new_node->str)
		ft_exit_error(ERR_ALLOC_STR);
	ft_strlcpy(new_node->str, temp, len + 1);
	new_node->quote.NONE = true;
	append_node(arg, new_node);
	return (temp + len);
}

/*
	1) Duplicate the original string to work on a separete memory space
	2) Navigate the string to see if we have to build a quote node ("" or ''),
		a toke node (|, <, >, <<, or >>), that will always be valid, or a simple node.
	3) Polish list to set up all the node correctly.
	4) Free the duplicated string.
*/
static void	parse_list(t_shell *shell)
{
	char	*temp;
	char	*original_temp;

	temp = ft_strdup(shell->line);
	original_temp = temp;
	while (*temp)
	{
		if (!*temp)
			break ;
		if (*temp == '\'' || *temp == '\"')
			temp = create_quote_node(&shell->arg, temp);
		else if (*temp == '|' || *temp == '<' || *temp == '>')
			temp = create_token_node(&shell->arg, temp);
		else if (*temp != ' ' && *temp != '\t' && *temp != '|'
				&& *temp != '<' && *temp != '>')
			temp = create_new_node(&shell->arg, temp);
		else
			temp++;
	}
	free(original_temp);
	polish_list(shell, shell->arg);
}

/*
	1) Read from the user input with readline
	2) Handle CTRL -D signal (EOF), exiting the shell
	3) Handle instant ENTER, displaying a new prompt
	4) Parse the lise into a list
	5) See if the command can go into the history
	6) Free the current read line
*/
void	parse_args(t_shell *shell)
{
	shell->line = readline("minishell$ ");
	if (!shell->line)
		handle_eof(shell);
	if (!shell->line[0])
	{
		handle_enter(shell);
		return ;
	}
	parse_list(shell);
	print_list(shell->arg);
	handle_history(shell);
	parse_matrix(shell);
	handle_builtin(shell);
	free(shell->line);
}
