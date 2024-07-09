#include "../include/minishell.h"

char	*copy_var(char *current_var);
char	*copy_name(char *current_var);
char	*copy_value(char *current_var);

static t_env	*find_last_env_node(t_env *env);

void	init_env(t_shell *shell, char **envp)
{
	char **current_var;

	current_var = envp;
	while (*current_var)
	{
		create_new_env_node(shell, *current_var);
		current_var++;
	}
}

void	create_new_env_node(t_shell *shell, char *current_var)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		ft_exit_error(ERR_ALLOC_ENV);
	new_node->var = copy_var(current_var);
	new_node->name = copy_name(current_var);
	new_node->value = copy_value(current_var);
	new_node->show = false;
	append_env_node(&shell->env, new_node);
}

void	append_env_node(t_env **env, t_env *new_node)
{
	t_env	*last_node;

	if (!*env)
	{
		*env = new_node;
		new_node->prev = new_node;
	}
	else
	{
		last_node = find_last_env_node(*env);
		last_node->next = new_node;
		new_node->prev = last_node;
	}
	new_node->next = NULL;
}

static t_env	*find_last_env_node(t_env *env)
{
	if (!env)
		return (NULL);
	while (env->next)
		env = env->next;
	return (env);
}
