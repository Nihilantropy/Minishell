#include "../../include/minishell.h"

static int	handle_home_cd(t_shell *shell);
static int	handle_path_cd(char *path);
static void	update_oldpwd(t_shell *shell, char *current_pwd);
static void	update_pwd(t_shell *shell, char *new_pwd);
void		create_oldpwd_node(t_shell *shell, char *current_pwd);
void		update_oldpwd_node(t_env *current_node, char *current_pwd);
void		create_pwd_node(t_shell *shell, char *new_pwd);
void		update_pwd_node(t_env *current_node, char *new_pwd);

/*	handle builtin cd:
**	1) saving the current workign directory in the stack
**	2) changing the current working directory with chdir
**	3) saving the new working directory in the stack
**	4) updating the oldpwd and the pwd in the env list
*/
void	handle_builtin_cd(t_shell *shell, char **matrix)
{
	char	current_pwd[2048];
	char	new_pwd[2048];
	int		cd_return;

	cd_return = 0;
	if (matrix_len(matrix) >= 3)
	{
		ft_putstr_fd(ERR_CD_PATH, 2);
		g_exit_status = EXIT_STATUS_ERROR;
		return ;
	}
	getcwd(current_pwd, 2048);
	if (matrix_len(matrix) == 1)
		cd_return = handle_home_cd(shell);
	else if (matrix[1])
	 	cd_return = handle_path_cd(matrix[1]);
	if (cd_return == -1)
	{
		g_exit_status = EXIT_STATUS_ERROR;
		return ;
	}
	else
	{
		getcwd(new_pwd, 2048);
		update_oldpwd(shell, current_pwd);
		update_pwd(shell, new_pwd);
		g_exit_status = EXIT_STATUS_SUCCESS;
	}
}

/*	update oldpwd:
**	if the OLDPWD node is not in the env list (ex. has been unset or the user never
**	moved from the start of the session), create the node.
**	else substitute the old value.
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
		update_pwd_node(current_node, current_pwd);
}

/*	update pwd:
**	if the PWD node is not in the env list (ex. has been unset or the user never
**	moved from the start of the session), create the node.
**	else update the old value.
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

static int	handle_home_cd(t_shell *shell)
{
	char	*home_path;

	home_path = ft_getenv(shell->env, "HOME");
	printf("home_path is: %s\n", home_path);
	if (!home_path)
	{
		ft_putstr_fd(ERR_HOME_CD, 2);
		return (-1);
	}
	else
	{
		if (chdir(home_path) == -1)
		{
			perror("chdir");
			return (-1);
		}
	}
	free(home_path);
	return (0);
}

static int	handle_path_cd(char *path)
{
	if (chdir(path) == -1)
	{
		perror("chdir");
		return (-1);
	}
	return (0);
}