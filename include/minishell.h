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
	false = 0,
	true = 1,
}	t_bool;

typedef	enum e_quote
{
	QUOTE_NONE = -1,
	QUOTE_SINGLE = 0,
	QUOTE_DOUBLE = 1
}	t_quote;

typedef struct s_token
{
	t_bool	is_token;
	t_bool	infile;
	t_bool	outfile;
	t_bool	append;
	t_bool	here_doc;
}			t_token;

typedef struct s_arg
{
	int				index;
	t_token			token;
	t_quote			quote;
	char			*str;
	struct s_arg	*next;
	struct s_arg	*prev;
}					t_arg;

typedef struct s_shell
{
	int		fd;
	char	*line;
	t_arg	*arg;
	char	**env;
	t_bool	add_to_history;
	int		pipe_nbr;
}			t_shell;

/* main utils */

/* init shell */
void	init_shell(t_shell *shell, char **envp);

/* parser */
void	parse_args(t_shell *shell);

/* parser utils */
void	handle_enter(t_shell *shell);

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


#endif

