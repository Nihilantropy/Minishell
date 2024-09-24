/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:43:34 by crea              #+#    #+#             */
/*   Updated: 2024/09/24 17:51:58 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int		check_exit_invalid_arg(t_shell *shell);
static t_bool	check_exit_alpha_arg(char **matrix);
static t_bool	check_exit_multi_arg(char **matrix);

void	handle_builtin_exit(t_shell *shell)
{
	g_exit_status = check_exit_invalid_arg(shell);
	if (g_exit_status == 3)
	{
		g_exit_status = 1;
		return ;
	}
	free_shell(shell);
	free_prompt(shell);
	exit(g_exit_status);
}

/*	check exit invalid arg:
**	1) if exit has no argument, return 0
**	2) if there are multiple arguments, return 1 (won't exit)
**	3) if argument is not a number, return 2
**	4) if all checks are passed, convert the exit number
**		using handle_exit_status
**	5) return status
*/
static int	check_exit_invalid_arg(t_shell *shell)
{
	char	**matrix;
	int		status;

	matrix = shell->cmd->matrix;
	status = 0;
	if (!matrix[1])
		return (0);
	if (check_exit_multi_arg(matrix) == true)
		return (3);
	if (check_exit_alpha_arg(matrix) == true)
		return (2);
	status = ft_atoi(matrix[1]);
	handle_exit_status(status);
	return (status);
}

static t_bool	check_exit_alpha_arg(char **matrix)
{
	if (ft_isdigit_str(matrix[1]) == 0)
		return (true);
	return (false);
}

static t_bool	check_exit_multi_arg(char **matrix)
{
	if (matrix[2] != NULL)
	{
		ft_putstr_fd("too many arguments\n", 2);
		return (true);
	}
	return (false);
}
