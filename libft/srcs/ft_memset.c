/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:59:10 by crea              #+#    #+#             */
/*   Updated: 2024/02/05 14:42:07 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memset(void *arr, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)arr;
	while (n-- > 0)
		*ptr++ = (unsigned char)c;
	return (arr);
}
