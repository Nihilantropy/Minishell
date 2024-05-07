/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:56:27 by crea              #+#    #+#             */
/*   Updated: 2024/02/05 14:46:05 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memchr(const void *s, int c, size_t sz)
{
	size_t	i;

	i = 0;
	while (i < sz)
	{
		if (((unsigned char *)s)[i] == (const unsigned char)c)
			return ((void *)(s + i));
		i++;
	}
	return (0);
}
