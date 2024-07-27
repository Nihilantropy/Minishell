#include "../../include/minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_shell		shell;

	if (argc != 1)
	{
		printf(ERR_NBR_ARG);
		return (0);
	}
	(void)argv;
	init_shell(&shell, envp);
	signal_handler();
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
		parse_args(shell);
		if (shell->arg && shell->error == false)
		{
			executor(shell);
		}
		free_prompt_lists(shell);
		shell->pipes_nbr = 0;
		shell->error = false;
	}
}
