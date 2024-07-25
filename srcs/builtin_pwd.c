#include "../include/minishell.h"

void	handle_builtin_pwd(t_shell *shell)
{
	char	pwd[2048];

	if (getcwd(pwd, 2048) != NULL)
	{
		printf("%s\n", pwd);
		shell->last_exit_status = EXIT_STATUS_SUCCESS;
	}
	else
	{
		shell->last_exit_status = EXIT_STATUS_ERROR;
		perror(ERR_PWD);
	}

}