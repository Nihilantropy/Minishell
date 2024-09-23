/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_command_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:57:33 by mcantell          #+#    #+#             */
/*   Updated: 2024/09/23 13:57:34 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_relative_path(t_cmd *current_node)
{
	int	i;

	if (!current_node->matrix[0])
		return (0);
	i = ft_strlen(current_node->matrix[0]) - 1;
	while (i >= 0)
	{
		if (current_node->matrix[0][i] == '/')
			return (1);
		i--;
	}
	return (0);
}

char	*extract_cmd(t_cmd *current_node)
{
	int		i;
	int		j;
	char	*cmd;

	i = ft_strlen(current_node->matrix[0]) - 1;
	j = 0;
	while (current_node->matrix[0][i] != '/' && current_node->matrix[0][i])
	{
		j++;
		i--;
	}
	cmd = malloc(j + 1);
	if (!cmd)
		ft_exit_error(ERR_CMD_ALLOC);
	j = 0;
	i++;
	while (current_node->matrix[0][i])
		cmd[j++] = current_node->matrix[0][i++];
	cmd[j] = '\0';
	return (cmd);
}

char	*find_cmd_path(t_shell *shell, t_cmd *current_node)
{
	int		i;
	char	*relative_path;
	char	*cmd_path;

	i = 0;
	while (shell->path[i])
	{
		relative_path = ft_strjoin(shell->path[i], "/");
		cmd_path = ft_strjoin(relative_path, current_node->matrix[0]);
		free(relative_path);
		if (!cmd_path)
			return (NULL);
		if (access(cmd_path, F_OK) == 0)
		{
			free_matrix(shell->path);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	free_matrix(shell->path);
	return (NULL);
}

void	check_path(t_shell *shell, t_cmd *current_node)
{
	if (!shell->path)
	{
		(void)current_node;
		ft_putstr_fd("-minishell:", 2);
		ft_putstr_fd(current_node->matrix[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(EXIT_FAILURE);
	}
}

