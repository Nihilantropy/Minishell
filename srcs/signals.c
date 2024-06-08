/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:50:45 by crea              #+#    #+#             */
/*   Updated: 2024/06/07 16:50:45 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	signal_handler(void)
{
	sigint_handler(SIGINT);
}


void	handle_sigint(int sig)
{
	(void)sig;
	printf("\n");
}

void	handle_eof(void)
{
	printf("EOF\n");
	exit(EXIT_SUCCESS);
}

void	sigint_handler(int signum)
{
	struct sigaction sa;

	(void)signum;
	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
}