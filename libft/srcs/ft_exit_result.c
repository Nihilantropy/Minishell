/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_result.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:04:47 by crea              #+#    #+#             */
/*   Updated: 2024/04/23 12:15:46 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_exit_error(char *error)
{
	ft_putstr_fd(error, 2);
	exit(EXIT_FAILURE);
}

void	ft_exit_success(char *success)
{
	ft_putstr_fd(success, 1);
	exit(EXIT_SUCCESS);
}
