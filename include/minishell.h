#ifndef MINISHELL_H
# define MINISHELL_H

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

# define EXIT_STATUS_SUCCESS 0
# define EXIT_STATUS_ERROR 1

# define HERE_DOC_SIGINT 130

extern int	g_exit_status;

typedef enum e_bool
{
	false = 0,
	true = 1,
}	t_bool;

typedef struct s_quote
{
	t_bool	none_q;
	t_bool	single_q;
	t_bool	double_q;
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

typedef struct s_env
{
	char			*var;
	char			*name;
	char			*value;
	t_bool			show;
	t_bool			chain;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

typedef struct s_here_doc
{
	char	*limiter;
	char	*tmp_file_name;
	t_bool	expand;
	int		index;
}			t_here_doc;

typedef struct s_redir_list
{
	char					*fd_name;
	t_here_doc				*here_doc;
	t_redir					type;
	struct s_redir_list		*next;
	struct s_redir_list		*prev;
}							t_redir_list;

typedef struct s_cmd
{
	int				index;
	char			**matrix;
	t_redir_list	*redir;
	t_builtin		builtin;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

typedef struct s_arg
{
	int				index;
	char			*str;
	t_token			token;
	t_redir			type;
	t_quote			quote;
	t_bool			chained;
	struct s_arg	*next;
	struct s_arg	*prev;
}					t_arg;

typedef struct s_shell
{
	char	**new_env;
	char	*line;
	t_bool	add_to_history;
	t_arg	*arg;
	t_cmd	*cmd;
	t_env	*env;
	char	**path;
	int		pipes_nbr;
	t_bool	error;
	int		stdin_copy;
	int		stdout_copy;
}			t_shell;

/*** main ***/
/* main */
void	shell_prompt(t_shell *shell);
/* main utils */
char	**dup_matrix(char **matrix);
/* history */
void	handle_history(t_shell *shell);
/* ft_getenv */
char	*ft_getenv(t_env *env, char *var_name);
/* init shell */
void	init_shell(t_shell *shell, char **envp);
/* init env */
void	init_env(t_shell *shell, char **envp);
void	create_new_env_node(t_shell *shell, char *current_var);
void	append_env_node(t_env **env, t_env *new_node);
/* init env utils */
char	*copy_var(char *current_var);
char	*copy_name(char *current_var);
char	*copy_value(char *current_var);
t_env	*find_last_env_node(t_env *env);

/*** signal ***/
/* signal */
void	signal_handler_interactive(void);
/* signal sigint */
void	sigint_handler(void);
/* signal sigquit */
void	sigquit_handler(void);
/* signal sigterm */
void	signal_sigterm(t_shell *shell);
/* signal sigint heredoc */
void	sigint_handler_heredoc(void);

/*** parser ***/
/* parser */
void	parse_args(t_shell *shell);
/* parser utils 1 */
t_arg	*init_new_node(void);
/* parser utils 2 */
int		arg_length(char *temp, t_arg *new_node);
int		token_length(char *temp);
/* parser list utls */
void	append_node(t_arg **arg, t_arg *new_node);
t_arg	*find_last_arg_node(t_arg *arg);
void	print_list(t_arg *arg);
void	free_list(t_arg **arg);
/* parser env */
void	handle_env_var(t_shell *shell, t_arg *arg);
char	*parse_env_var(t_shell *shell, char *str);
/* parser polish list */
void	polish_list(t_shell *shell, t_arg *arg);
/* parser polish list utils */
int		check_arg_list(t_shell *shell);
/* parser cmd */
void	parse_matrix(t_shell *shell);
/* parser cmd utils */
int		len_to_pipe_cmd(t_arg *arg);
void	copy_command(t_cmd *cmd, t_shell *shell);
/* parser cmd list */
void	append_cmd_node(t_cmd **cmd, t_cmd *new_node);
void	append_redir_node(t_redir_list **redir, t_redir_list *new_node);
/* parser cmd redir */
void	build_redir_list(t_cmd *cmd, t_shell *shell);
/* parser cmd redir utils */
void	append_redir_node(t_redir_list **redir, t_redir_list *new_node);
void	set_node_type(t_redir_list *redir, t_arg *current_node);
/* parser heredoc */
void	handle_heredoc(t_shell *shell);

/*** builtin ***/
/* builtin */
void	check_builtin(t_cmd *cmd);
void	handle_builtin(t_shell *shell, t_cmd *current_node);
/* builtin export */
void	handle_builtin_export(t_shell *shell, char **matrix);
/* builtin export utils 1 */
void	dup_ex_list(t_env *export, t_env **export_dup);
void	chain_env_value(t_env *current_node, t_env *new_node);
/* builtin export utils 2 */
int		var_length(char *line);
char	*copy_ex_var(char *str);
char	*copy_ex_name(t_env *current_node, char *current_var);
char	*copy_ex_value(char *current_var);
/* builtin export print */
void	print_export(t_env *env);
/* builtin export print utils */
void	sort_nodes(t_env **env_dup);
/* builtin env */
void	handle_builtin_env(t_shell *shell);
void	remove_node(t_env *current_node, t_env **head);
/* builtin unset */
void	handle_builtin_unset(t_shell *shell, char **matrix);
/* builtin unset utils */
void	create_unset_list(char **matrix, t_env **unset);
/* builtin echo */
void	handle_builtin_echo(char **matrix, t_redir_list *redir);
/* builtin pwd */
void	handle_builtin_pwd(void);
/* builtin exit */
void	handle_builtin_exit(t_shell *shell);
/* builtin cd */
void	handle_builtin_cd(t_shell *shell, char **matrix);

/*** executor ***/
/* executor */
void	executor(t_shell *shell);
int		handle_exit_status(int status);
/* executor redir */
void	redir_input(t_redir_list *redir);
void	redir_output(t_redir_list *redir);
void	reset_redir(t_shell *shell);
/* executor process */
void	process_command(t_shell *shell);
/* executor command */
void	exe_cmd(t_shell *shell, t_cmd *current_node);

/*** utils ***/
/* main */
void	free_prompt(t_shell *shell);
void	free_shell(t_shell *shell);
/* matrix */
void	print_matrix(char **matrix);
void	free_matrix(char **matrix);
/* cmd */
void	print_cmd_list(t_cmd *cmd);
void	free_cmd_list(t_cmd **cmd);
/* redir */
void	print_redir_list(t_cmd *cmd);
void	free_all_redir_list(t_cmd *cmd);
void	free_redir_list(t_redir_list **redir);
/* env */
void	print_env_list(t_env *env);
void	free_env_list(t_env **env);

#endif
