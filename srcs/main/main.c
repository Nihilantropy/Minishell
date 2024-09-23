/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:44:38 by crea              #+#    #+#             */
/*   Updated: 2024/09/23 14:53:21 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	g_exit_status = 0;

int	main(int argc, char **argv, char **envp)
{
	t_shell		shell;

	if (argc != 1)
	{
		ft_putstr_fd(ERR_NBR_ARG, 2);
		return (1);
	}
	(void)argv;
	init_shell(&shell, envp);
	shell_prompt(&shell);
	return (0);
}

void	shell_prompt(t_shell *shell)
{
	while (1)
	{
		signal_handler_interactive();
		parse_args(shell);
		if (shell->arg && shell->error == false
			&& g_exit_status != HERE_DOC_SIGINT)
			executor(shell);
		shell->pipes_nbr = 0;
		shell->error = false;
		free_prompt(shell);
	}
}
