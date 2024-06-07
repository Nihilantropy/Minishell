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
	shell->line = get_next_line(STDIN_FILENO);
	shell->matrix = ft_split(shell->line, ' ');
	free(shell->line);
	return ;
}