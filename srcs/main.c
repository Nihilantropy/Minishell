/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:53:58 by crea              #+#    #+#             */
/*   Updated: 2024/05/06 15:53:58 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv)
{
	if (argc < 1)
		ft_exit_error(ERR_NBR_ARG);
	ft_printf("Hi there! Is minishell! %s\n", argv[1]);
}