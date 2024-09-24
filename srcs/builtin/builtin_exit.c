/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:43:34 by crea              #+#    #+#             */
/*   Updated: 2024/09/24 13:31:10 by crea             ###   ########.fr       */
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

static int	check_exit_invalid_arg(t_shell *shell)
{
	char	**matrix;

	matrix = shell->cmd->matrix;
	if (!matrix[1])
		return (0);
	if (check_exit_multi_arg(matrix) == true)
		return (3);
	if (check_exit_alpha_arg(matrix) == true)
		return (2);
	g_exit_status = ft_atoi(matrix[1]);
	handle_exit_status(g_exit_status);
	return (g_exit_status);
}

static t_bool	check_exit_alpha_arg(char **matrix)
{
	int	x;

	x = 0;
	while (matrix[1][x])
	{
		if (!ft_isdigit(matrix[1][x]))
		{
			ft_putstr_fd("\n-minishell: exit: ", 2);
			ft_putstr_fd(matrix[1], 2);
			ft_putstr_fd(": \n", 2);
			ft_putstr_fd("numeric argument required\n", 2);
			return (true);
		}
		x++;
	}
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
