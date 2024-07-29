#include "../../include/minishell.h"

static char	**find_total_path(char **envp);

/*
	Init the main shell struct
*/
void	init_shell(t_shell *shell, char **envp)
{
	shell->fd = STDIN_FILENO;
	shell->line = NULL;
	shell->add_to_history = true;
	shell->arg = NULL;
	shell->pipes_nbr = 0;
	shell->env = NULL;
	init_env(shell, envp);
	shell->path = find_total_path(envp);
	shell->last_exit_status = 0;
	shell->cmd = NULL;
	shell->error = false;
	shell->envp_d = envp;
}

/*
	Find the PATH for the executable
*/
static char	**find_total_path(char **envp)
{
	char	**path;
	int		i;

	i = 0;
	while (envp[i] && !ft_strnstr(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
	{
		printf("NA NA NA! Give me the path asshole!\n");
		return (NULL);
	}
	path = ft_split(envp[i] + 5, ':');
	return (path);
}