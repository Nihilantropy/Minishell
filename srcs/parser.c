/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:12:46 by crea              #+#    #+#             */
/*   Updated: 2024/06/07 16:12:46 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parse_args(t_shell *shell)
{
	shell->line = readline("minishell$");
	if (!shell->line)
		handle_eof();
	if (shell->line && (shell->line[0]))
	{
		handle_history(shell);
		shell->matrix = ft_split(shell->line, ' ');
	}
	else
	{
		shell->matrix = NULL;
		free(shell->line);
	}
	return ;
}