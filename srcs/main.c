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
	(void)envp;
	init_shell(&shell, envp);
	signal_handler();
	if (isatty(STDIN_FILENO))
	{
		while (1)
		{
			parse_args(&shell);
			if (shell.arg && !ft_strncmp(shell.arg->str, "exit", 5))
			{
				printf("exit MAIN\n");
				exit(EXIT_SUCCESS);
			}
			else if (shell.arg)
			{
				print_list(shell.arg);
				//executor(&shell, envp);
			}
			free_list(&shell.arg);
		}
	}
	return 0;
}