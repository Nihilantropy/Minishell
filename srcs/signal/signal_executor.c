/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_executor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:45:21 by crea              #+#    #+#             */
/*   Updated: 2024/09/23 13:45:22 by crea             ###   ########.fr       */
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