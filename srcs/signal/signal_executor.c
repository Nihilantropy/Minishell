/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_executor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:58:39 by mcantell          #+#    #+#             */
/*   Updated: 2024/09/23 13:58:40 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	signal_handler_execve(int signum)
{
	if (signum == SIGINT)
		g_exit_status = 130;
	if (signum == SIGQUIT)
		g_exit_status = 131;
}