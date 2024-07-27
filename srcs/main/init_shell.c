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
	char	**total_path;
	char	*temp;
	int		i;

	i = 0;
	while (!ft_strnstr(envp[i], "PATH=", 5))
		i++;
	total_path = ft_split(envp[i] + 5, ':');
	i = 0;
	while (total_path[i])
	{
		temp = total_path[i];
		total_path[i] = ft_strjoin(total_path[i], "/");
		i++;
		free(temp);
	}
	return (total_path);
}