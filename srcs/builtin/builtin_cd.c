#include "../../include/minishell.h"

static int	handle_home_cd(t_shell *shell);
static int	handle_path_cd(t_env *env, char *path);
static void	update_oldpwd(t_shell *shell, char *current_pwd);
static void	update_pwd(t_shell *shell, char *new_pwd);

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
	else if (matrix_len(matrix) == 2)
	 	cd_return = handle_path_cd(shell->env, matrix[1]);
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
		return ;
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
		return ;
	else
		update_pwd_node(current_node, new_pwd);
}

/*	handle home cd:
**	if command is "cd" with no path,
**	get the HOME env var value and use
**	chdir function to enter the user 
**	home directory
*/
static int	handle_home_cd(t_shell *shell)
{
	char	*home_path;

	home_path = ft_getenv(shell->env, "HOME");
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
	return (0);
}

static int	handle_path_cd(t_env *env, char *path)
{
	char	*old_pwd;

	if (ft_strcmp(path, "-") == 0)
	{
		old_pwd = ft_getenv(env, "OLDPWD");
		if (!old_pwd)
		{
			ft_putstr_fd(ERR_OLDPWD_UNSET, 2);
			return (-1);
		}
		if (chdir(old_pwd) == -1)
		{
			perror("chdir");
			return (-1);
		}
		printf("%s\n", old_pwd);
	}
	else if (chdir(path) == -1)
	{
		perror("chdir");
		return (-1);
	}
	return (0);
}