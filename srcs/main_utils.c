/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:17:46 by crea              #+#    #+#             */
/*   Updated: 2024/06/07 16:17:46 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_all(t_shell *shell)
{
	free_env_list(&shell->env);
}

void	print_matrix(char **matrix)
{
	int	y;

	y = 0;
	while (matrix[y])
	{
		printf("matrix[%d]: %s\n", y, matrix[y]);
		y++;
	}
}

void	free_matrix(char **matrix)
{
	int	y;

	y = 0;
	while (matrix[y])
		free(matrix[y++]);
	free(matrix);
}