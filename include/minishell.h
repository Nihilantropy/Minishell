/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:54:01 by crea              #+#    #+#             */
/*   Updated: 2024/06/04 21:47:34 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdarg.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "messages.h"
# include "../libft/include/libft.h"

typedef struct s_shell
{
	int			fd;
	char		*line;
	char		**matrix;
	char		**env;
}				t_shell;

/* main utils */
void	print_matrix(char **matrix);
void	free_matrix(char **matrix);
void	free_shell(t_shell *shell);

/* init shell */
void	init_shell(t_shell *shell, char **envp);

/* parser */
void	parse_args(t_shell *shell);

/* signal handler */
void	signal_handler(void);
void	handle_sigint(int sig);
void	handle_eof(void);
void	sigint_handler(int signum);

/* history */
void	handle_history(t_shell *shell);

#endif

