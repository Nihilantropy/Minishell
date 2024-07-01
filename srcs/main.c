/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:53:58 by crea              #+#    #+#             */
/*   Updated: 2024/06/04 21:49:51 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_shell		shell;

	if (argc != 1)
	{
		printf(ERR_NBR_ARG);
		return (0);
	}
	(void)argv;
	init_shell(&shell, envp);
	signal_handler();
	if (isatty(STDIN_FILENO))
	{
		while (1)
		{
			if (!parse_args(&shell))
				printf("error pipe\n");
			else if (shell.arg && !ft_strncmp(shell.arg->str, "exit", 5))
			{
				printf(EXIT_MAIN);
				exit(EXIT_SUCCESS);
			}
			else if (shell.arg)
			{
				//executor(&shell, envp);
			}
			shell.pipes_nbr = 0;
			free_redir_list(&shell.cmd->redir);
			free_cmd_list(&shell.cmd);
			free_list(&shell.arg);
		}
	}
	return 0;
}