#include "../include/minishell.h"

/*
	Initializing the new node to have all known values
*/
t_arg	*init_new_node(void)
{
	t_arg	*new_node;

	new_node = (t_arg *)malloc(sizeof(t_arg));
	if (!new_node)
		ft_exit_error(ERR_ALLOC_NEW_NODE);
	new_node->index = 0;
	new_node->str = NULL;
	new_node->token.pipe = false;
	new_node->token.t_infile = false;
	new_node->token.t_outfile = false;
	new_node->token.t_here_doc = false;
	new_node->token.t_append = false;
	new_node->type.infile = false;
	new_node->type.outfile = false;
	new_node->type.here_doc = false;
	new_node->type.append = false;
	new_node->quote.DOUBLE = false;
	new_node->quote.SINGLE = false;
	new_node->quote.NONE = false;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
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
