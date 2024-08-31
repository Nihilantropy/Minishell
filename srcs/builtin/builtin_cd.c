#include "../../include/minishell.h"

static void	update_oldpwd(t_shell *shell, char *current_pwd);
static void	update_pwd(t_shell *shell, char *new_pwd);
void		create_oldpwd_node(t_shell *shell, char *current_pwd);
void		update_oldpwd_node(t_env *current_node, char *current_pwd);
void		create_pwd_node(t_shell *shell, char *new_pwd);
void		update_pwd_node(t_env *current_node, char *new_pwd);

/*	handle builtin cd:
		1) saving the current workign directory in the stack
		2) changing the current working directory with chdir
		3) saving the new working directory in the stack
		4) updating the oldpwd and the pwd in the env list
*/
void	handle_builtin_cd(t_shell *shell, char **matrix)
{
	char	current_pwd[2048];
	char	new_pwd[2048];

	if (!matrix[1] || matrix[2])
	{
		printf(ERR_CD_PATH);
		shell->last_exit_status = EXIT_STATUS_SUCCESS;
		return ;
	}
	getcwd(current_pwd, 2048);
	if (chdir(matrix[1]) == -1)
	{
		perror("minishell");
		shell->last_exit_status = EXIT_STATUS_ERROR;
		return ;
	}
	else
	{
		getcwd(new_pwd, 2048);
		update_oldpwd(shell, current_pwd);
		update_pwd(shell, new_pwd);
		shell->last_exit_status = EXIT_STATUS_SUCCESS;
	}
}

/*	update oldpwd:
		If the OLDPWD node is not in the env list
		(ex. has been unset or the user never
		moved from the start of the session), create the node.
		Else substitute the old value.
*/
static void	update_oldpwd(t_shell *shell, char *current_pwd)
{
	t_env	*current_node;

	current_node = shell->env;
	while (current_node)
	{
		if (!ft_strncmp(current_node->name, "OLDPWD=", 8))
			break ;
		current_node = current_node->next;
	}
	if (!current_node)
		create_oldpwd_node(shell, current_pwd);
	else
		update_oldpwd_node(current_node, current_pwd);
}

/*	update pwd:
		If the PWD node is not in the env list
		(ex. has been unset or the user never
		moved from the start of the session), create the node.
		Else update the old value.
*/
static void	update_pwd(t_shell *shell, char *new_pwd)
{
	t_env	*current_node;

	current_node = shell->env;
	while (current_node)
	{
		if (!ft_strncmp(current_node->name, "PWD=", 5))
			break ;
		current_node = current_node->next;
	}
	if (!current_node)
		create_pwd_node(shell, new_pwd);
	else
		update_pwd_node(current_node, new_pwd);
}
