#include "../include/minishell.h"

void	append_node(t_arg **arg, t_arg *new_node)
{
	t_arg	*last_node;

	if (!*arg)
	{
		*arg = new_node;
		new_node->prev = new_node;
	}
	else
	{
		last_node = find_last_node(*arg);
		last_node->next = new_node;
		new_node->prev = last_node;
	}
	new_node->next = NULL;
}

t_arg	*find_last_node(t_arg *arg)
{
	if (!arg)
		return (NULL);
	while (arg->next)
		arg = arg->next;
	return (arg);
}

void	print_list(t_arg *arg)
{
	if (!arg)
		return ;
	while (arg)
	{
		printf("\nstr: %s\n", arg->str);
		printf("new_node-str pointer is: %p\n", arg->str);
		printf("index: %d\n", arg->index);
		if (arg->token.pipe)
			printf("token = pipe\n");
		else if (arg->token.infile)
			printf("token = infile\n");
		else if (arg->token.outfile)
			printf("token = outfile\n");
		else if (arg->token.here_doc)
			printf("token = here_doc\n");
		else if (arg->token.append)
			printf("token = append\n");
		if (arg->quote.NONE)
			printf("not quoted\n");
		else if (arg->quote.SINGLE)
			printf("single quoted\n");
		else if (arg->quote.DOUBLE)
			printf("double quoted\n");
		printf("------------------\n");
		arg = arg->next;
	}
}

void	free_list(t_arg **arg)
{
	t_arg	*current;
	t_arg	*next_node;

	if (!*arg)
		return ;
	current = *arg;
	while (current)
	{
		next_node = current->next;
		free(current->str);
		free(current);
		current = next_node;
	}
	*arg = NULL;
}