/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:45:24 by crea              #+#    #+#             */
/*   Updated: 2024/09/23 13:45:25 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	signal_handler(int signum);
static void	ign(int signum);

/*	signal handler interactive:
**	Handle signals SIGINT & SIGQUIT for interactive mode
*/
void	signal_handler_interactive(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
	signal(SIGTERM, signal_handler);
}

static void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_status = EXIT_FAILURE;
		printf("\n\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signum == SIGTERM)
		exit (EXIT_SUCCESS);
}

void signal_ign(void)
{
	signal(SIGQUIT, ign);
	signal(SIGINT, ign);
	signal(SIGTERM, ign);
}

static void	ign(int signum)
{
	if (signum)
		return ;
}
