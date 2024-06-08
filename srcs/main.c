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

int main()
{
	t_shell		shell;

	init_shell(&shell);
	signal_handler();
	if (isatty(STDIN_FILENO))
	{
		printf("Input from terminal.\n");
		while (1)
		{
			parse_args(&shell);
			if (!shell.matrix[0] || !ft_strncmp(shell.matrix[0], "exit", 4))
			{
				printf("exit command called\n");
				exit(EXIT_SUCCESS);
			}
			else
			{
				print_matrix(shell.matrix);
			}
		}
		
	}
	else
	{
		printf("Input from file.\n");
	}
	return 0;
}