#include "../../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell		shell;

	if (argc != 1)
	{
		ft_putstr_fd(ERR_NBR_ARG, 2);
		return (1);
	}
	(void)argv;
	init_shell(&shell, envp);
	if (isatty(STDIN_FILENO))
	{
		shell_prompt(&shell);
	}
	return (0);
}

void	shell_prompt(t_shell *shell)
{
	while (1)
	{
		signal_handler_interactive();
		parse_args(shell);
		if (shell->arg && shell->error == false)
		{
			executor(shell);
		}
		shell->pipes_nbr = 0;
		shell->error = false;
	}
}
