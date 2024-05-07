/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:57:14 by crea              #+#    #+#             */
/*   Updated: 2024/02/05 14:42:07 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t len)
{
	if (!dest && !src)
		return (0);
	while (len--)
		*(unsigned char *)(dest + len) = *(unsigned char *)(src + len);
	return (dest);
}
