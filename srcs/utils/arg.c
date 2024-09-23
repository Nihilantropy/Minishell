/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:58:45 by mcantell          #+#    #+#             */
/*   Updated: 2024/09/23 13:58:46 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
void	print_list(t_arg *arg)
{
	if (!arg)
		return ;
	while (arg)
	{
		printf("\nstr: %s\n", arg->str);
		printf("new_node-str pointer is: %p\n", arg->str);
		printf("index: %d\n", arg->index);
		if (arg->token.is_token)
			printf("Is a token\n");
		else if (arg->type.is_redir)
			printf("Is a redirection\n");
		if (arg->token.pipe)
			printf("token = pipe\n");
		else if (arg->token.t_infile)
			printf("token = infile\n");
		else if (arg->token.t_outfile)
			printf("token = outfile\n");
		else if (arg->token.t_here_doc)
			printf("token = here_doc\n");
		else if (arg->token.t_append)
			printf("token = append\n");
		else if (arg->type.infile)
			printf("type = infile\n");
		else if (arg->type.outfile)
			printf("type = outfile\n");
		else if (arg->type.here_doc)
			printf("type = here_doc\n");
		else if (arg->type.append)
			printf("redir = append\n");
		if (arg->quote.none_q)
			printf("not quoted\n");
		else if (arg->quote.single_q)
			printf("single_q quoted\n");
		else if (arg->quote.double_q)
			printf("double_q quoted\n");
		if (arg->chained)
			printf("chained to next node\n");
		printf("------------------\n");
		arg = arg->next;
	}
}
*/

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
		if (current->str)
			free(current->str);
		free(current);
		current = next_node;
	}
	*arg = NULL;
}
