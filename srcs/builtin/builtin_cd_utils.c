#include "../../include/minishell.h"

void	create_oldpwd_node(t_shell *shell, char *current_pwd)
{
	char	*current_pwd_dup;
	char	*oldpwd_var;

	current_pwd_dup = ft_strdup(current_pwd);
	oldpwd_var = ft_strjoin("OLDPWD=", current_pwd_dup);
	free(current_pwd_dup);
	create_new_env_node(shell, oldpwd_var);
	free(oldpwd_var);
}

void	substitute_oldpwd_node(t_env *current_node, char *current_pwd)
{
	char	*current_pwd_dup;

	current_pwd_dup = ft_strdup(current_pwd);
	if (current_node->value)
		free(current_node->value);
	current_node->value = current_pwd_dup;
}

void	create_pwd_node(t_shell *shell, char *new_pwd)
{
	char	*new_pwd_dup;
	char	*pwd_var;

	new_pwd_dup = ft_strdup(new_pwd);
	pwd_var = ft_strjoin("PWD=", new_pwd_dup);
	free(new_pwd_dup);
	create_new_env_node(shell, pwd_var);
	free(pwd_var);
}

void	substitute_pwd_node(t_env *current_node, char *new_pwd)
{
	char	*new_pwd_dup;

	new_pwd_dup = ft_strdup(new_pwd);
	if (current_node->value)
		free(current_node->value);
	current_node->value = new_pwd_dup;
}