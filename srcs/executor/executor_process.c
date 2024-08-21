#include "../../include/minishell.h"

//static void	process_child(t_shell *shell, t_cmd *current_node, int fd[2]);
//static void	process_parent(t_shell *shell, t_cmd *current_node);
void		handle_exit_status(t_shell *shell, int status);








void process_command(t_shell *shell) {
    int fd[2];
    t_cmd *current_node = shell->cmd;
    pid_t pid;

    while (current_node) {
        if (pipe(fd) == -1)
            ft_exit_error("pipe");

        pid = fork();
        if (pid == -1)
            ft_exit_error("fork");

        if (pid == 0) {
            if (current_node->next)
                dup2(fd[1], STDOUT_FILENO);
            close(fd[0]);
            close(fd[1]);

            redir_input(current_node->redir);
            redir_output(current_node->redir);
            if (current_node->builtin.is_builtin)
                handle_builtin(shell, current_node);
            else if (current_node->matrix[0])
                exe_cmd(shell, current_node);
            else
                ft_exit_error("");
            exit(EXIT_SUCCESS);
        } else {
            close(fd[1]);
            if (current_node->next)
                dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
            current_node = current_node->next;
        }
    }
    int status;
    while (wait(&status) > 0)
		handle_exit_status(shell, status);
	exit(EXIT_SUCCESS);
}



/*
void	process_command(t_shell *shell)
{
	int		fd[2];
	t_cmd	*current_node;
	int		status;

	current_node = shell->cmd;
	while (current_node)
	{
		if (pipe(fd) == -1)
			ft_exit_error(ERR_PIPE);
		process_child(shell, current_node, fd);
		close(fd[1]);
		if (current_node->next)
			dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		current_node = current_node->next;
	}
	while (wait(&status) > 0)
		handle_exit_status(shell, status);
	exit(EXIT_SUCCESS);
}

static void	process_child(t_shell *shell, t_cmd *current_node, int fd[2])
{
    pid_t pid;

    pid = fork();
    if (pid == -1)
        ft_exit_error(ERR_FORK);
    if (pid == 0)
    {
        if (current_node->next)
            dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        redir_input(shell, current_node->redir);
        redir_output(current_node->redir);
        if (current_node->builtin.is_builtin)
            handle_builtin(shell, current_node);
        else if (current_node->matrix[0])
            exe_cmd(shell, current_node);
        else
            ft_exit_error("");
        exit(EXIT_SUCCESS);
    }
}*/

/*
	1) Create the fd[2] for the pipe communications between process 
		(fd[0]=read, fd[1]=write)
	2) The child process handle all the command exept the last one. 
		In case there is just one command, only the parent process is called
	3) Once each child process has finish his execution, the input is 
		redirected to the read pipe (the write pipe is handled in the 
		child process itself)
	4) Loop all the command list untill the last node
	5) The parent process handle the last command node

void	process_command(t_shell *shell)
{
	int		fd[2];
	int		i;
	t_cmd	*current_node;
	int		status;

	i = 0;
	current_node = shell->cmd;
	while (i <= shell->pipes_nbr)
	{
		if (pipe(fd) == -1)
			ft_exit_error(ERR_PIPE);
		process_child(shell, current_node, fd);
		close(fd[1]);
		if (i < shell->pipes_nbr)
			dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		current_node = current_node->next;
		i++;
	}
	while (wait(&status) > 0)
		handle_exit_status(shell, status);
	//process_parent(shell, current_node);
}*/

/*
	1) Fork the current process to write the output of the child, one the
		write pipe (fd[1])
	2) Redir the input and the output based on the redir list in the command node
	3) Execute the builtin, or the command if exist

static void	process_child(t_shell *shell, t_cmd *current_node, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_exit_error(ERR_FORK);
	if (pid == 0)
	{
		if (current_node->next)
			dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		redir_input(shell, current_node->redir);
		redir_output(current_node->redir);
		if (current_node->builtin.is_builtin)
		{
			handle_builtin(shell, current_node);
			exit(EXIT_SUCCESS);
		}
		else if (current_node->matrix[0])
			exe_cmd(shell, current_node);
		else
			ft_exit_error("");
	}
}*/

/*
	1) Redir the input and the output based on the redir list in the command node
	2) Execute the builtin, or the command if exist

static void	process_parent(t_shell *shell, t_cmd *current_node)
{
	redir_input(shell, current_node->redir);
	redir_output(current_node->redir);
	if (current_node->builtin.is_builtin)
	{
		handle_builtin(shell, current_node);
		exit(EXIT_SUCCESS);
	}
	else if (current_node->matrix[0])
		exe_cmd(shell, current_node);
	else
		ft_exit_error("");
}
*/