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
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "messages.h"
# include "../libft/include/libft.h"

typedef	enum e_bool
{
	false,
	true
}	t_bool;

typedef struct s_redir
{
	t_bool	here_doc;
	t_bool	redirection;
	int		infile_index;
	int		outfile_index;
	int		limiter_index;
}			t_redir;

typedef struct s_cmd
{
	int		index;
	int		pipes_nbr;
	char	*command;
	t_redir	redir;
}			t_cmd;

typedef struct s_shell
{
	t_cmd	cmd;
	int		fd;
	char	*line;
	char	**matrix;
	char	**matrix_utils;
	char	**env;
}			t_shell;

/* main utils */
void	print_matrix(char **matrix);
void	free_matrix(char **matrix);
void	free_shell(t_shell *shell);

/* init shell */
void	init_shell(t_shell *shell, char **envp);

/* parser */
void	parse_args(t_shell *shell);

/* parser utils */
void	handle_enter(t_shell *shell);
void	count_pipes(t_shell *shell);
void	remove_spaces(char **matrix);

/* signal handler */
void	signal_handler(void);
void	handle_sigint(int sig);
void	handle_eof(void);
void	sigint_handler(int signum);

/* history */
void	handle_history(t_shell *shell);

/* executor */
void	executor(t_shell *shell, char **envp);
void	exe_cmd(t_shell *shell, char *command, char **envp);
char	*find_cmd_path(t_shell *shell, char *command);

/* executor pipe */
//void	ft_here_doc(t_shell *shell, char **envp);
//void	ft_pipex(t_shell *shell, char **envp);
void	process_child(t_shell *shell, char *command, char **envp);
void	process_parent(t_shell *shell, char *command, char **envp);

char **ft_split_plus(const char *str, const char *sep_set);
char **ft_split_plus_utils(const char *str, const char *sep_set);

#endif

