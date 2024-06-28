#include "../include/minishell.h"

t_arg	*init_new_node()
{
	t_arg	*new_node;

	new_node = (t_arg *)malloc(sizeof(t_arg));
	if (!new_node)
		ft_exit_error("ERR MALLOC NEW NODE");
	new_node->index = 0;
	new_node->str = NULL;
	new_node->token.pipe = false;
	new_node->token.t_infile = false;
	new_node->token.t_outfile = false;
	new_node->token.t_here_doc = false;
	new_node->token.t_append = false;
	new_node->token.infile = false;
	new_node->token.outfile = false;
	new_node->token.here_doc = false;
	new_node->token.append = false;
	new_node->quote.DOUBLE = false;
	new_node->quote.SINGLE = false;
	new_node->quote.NONE = false;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	struct_list(t_arg **arg, t_arg *new_node)
{
	if ((new_node->quote.NONE || new_node->quote.DOUBLE)
		&& new_node->str && ft_strchr(new_node->str, '$'))
		handle_env_var(new_node);
	append_node(arg, new_node);
	set_node_index(new_node);
	set_fd_flag(*arg);
}

void	set_node_index(t_arg *new_node)
{
	if (new_node->prev == new_node)
		new_node->index = 1;
	else
		new_node->index = new_node->prev->index + 1;
}

int	arg_length(char *temp)
{
	int		i;
	char	quote;

	i = 0;
	if (temp[0] == '\"' || temp[0] == '\'')
	{
		i++;
		quote = *temp;
		while (temp[i] != quote && temp[i])
			i++;
		return (i);
	}
	else
	{
		while ((temp[i] != '\'' && temp[i] != '\"'
				&& temp[i] != '>' && temp[i] != '<'
				&& temp[i] != '|' && temp[i] != ' '
				&& temp[i] != '\t') && temp[i])
			i++;
		return (i);
	}
	return (i);
}

int	token_length(char *temp)
{
	char	token;

	token = *temp;
	if (token == '|')
		return (1);
	else if (token == '<' || token == '>')
	{
		if (temp[1] == token)
			return (2);
		else
			return (1);
	}
	return (0);
}
