/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:43:38 by mcantell          #+#    #+#             */
/*   Updated: 2024/06/20 15:44:04 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_struct(t_arg **arg)
{
	t_arg	*tmp;

	if (!arg)
		return ;
	while (*arg)
	{
		tmp = (*arg)->next;
		free ((*arg)->str);
		free (*arg);
		*arg = tmp;
	}
	arg = NULL;
}
