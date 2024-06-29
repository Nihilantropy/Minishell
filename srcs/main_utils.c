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

void	print_matrix(char ***matrix)
{
	int	z;
	int	y;

	z = 0;
	while (matrix[z])
	{
		y = 0;
		while (matrix[z][y])
		{
			printf("matrix[%d][%d]: %s\n", z, y, matrix[z][y]);
			y++;
		}
		z++;
	}
}

void	free_matrixes(char ***matrix)
{
	int	z;
	int	y;

	z = 0;
	while (matrix[z])
	{
		y = 0;
		while (matrix[z][y])
			free(matrix[z][y++]);
		free(matrix[z++]);
	}
	free(matrix);
}