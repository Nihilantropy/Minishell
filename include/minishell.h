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

typedef	struct s_quote
{
	t_bool	NONE;
	t_bool	SINGLE;
	t_bool	DOUBLE;
}			t_quote;

typedef struct s_token
{
	t_bool	is_token;
	t_bool	pipe;
	t_bool	t_infile;
	t_bool	t_outfile;
	t_bool	t_append;
	t_bool	t_here_doc;
}			t_token;

typedef struct s_redir
{
	t_bool	is_redir;
	t_bool	infile;
	t_bool	outfile;
	t_bool	append;
	t_bool	here_doc;
}			t_redir;

typedef struct s_builtin
{
	t_bool	is_builtin;
	t_bool	echo;
	t_bool	cd;
	t_bool	pwd;
	t_bool	export;
	t_bool	unset;
	t_bool	env;
	t_bool	exit;
}			t_builtin;

typedef struct s_arg
{
	int				index;
	char			*str;
	t_token			token;
	t_redir			type;
	t_quote			quote;
	struct s_arg	*next;
	struct s_arg	*prev;
}					t_arg;

typedef struct s_redir_list
{
	char					*fd_name;
	t_redir					type;
	struct s_redir_list		*next;
	struct s_redir_list		*prev;
}							t_redir_list;

typedef struct s_cmd
{
	char			**matrix;
	t_redir_list	*redir;
	t_builtin		builtin;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

typedef struct s_shell
{
	int		fd;
	char	*line;
	t_bool	add_to_history;
	t_arg	*arg;
	t_cmd	*cmd;
	char	**env;
	int		last_exit_status;
	int		pipes_nbr;
}			t_shell;

/* main utils */
void	print_matrix(char **matrix);
void	free_matrix(char **matrix);

/* init shell */
void	init_shell(t_shell *shell, char **envp);

/* parser */
void	parse_args(t_shell *shell);

/* parser utils */
t_arg	*init_new_node(void);
int		arg_length(char *temp);
int		token_length(char *temp);

/* parser list utls */
void	append_node(t_arg **arg, t_arg *new_node);
t_arg	*find_last_node(t_arg *arg);
void	print_list(t_arg *arg);
void	free_list(t_arg **arg);

/* parser env variables */
void	handle_env_var(t_shell *shell, t_arg *arg);

/* parser polish list */
void	polish_list(t_shell *shell, t_arg *arg);

/* parser matrix */
void	parse_matrix(t_shell *shell);

/* parser matrix utils */
int		len_to_pipe_cmd(t_arg *arg);
void	copy_command(t_cmd *cmd, t_shell *shell);
void	copy_redir(t_redir_list *redir, t_shell *shell);

/* parser matrix list */
void	append_cmd_node(t_cmd **cmd, t_cmd *new_node);
void	append_redir_node(t_redir_list **redir, t_redir_list *new_node);

/* parser matrix list utils */
void	print_cmd_list(t_cmd *cmd);
void	print_redir_list(t_cmd *cmd);
void	free_cmd_list(t_cmd **cmd);
void	free_redir_list(t_cmd *cmd);

/* signal handler */
void	signal_handler(void);
void	handle_sigint(int sig);
void	handle_eof(void);
void	sigint_handler(int signum);

/* signal utils */
void	handle_enter(t_shell *shell);

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



// TODO 
// create matrix with all command and flag in order and place redirection
// fd at the last index of the matrix.

#endif

