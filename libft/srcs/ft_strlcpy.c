/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:02:34 by crea              #+#    #+#             */
/*   Updated: 2024/02/05 14:43:16 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t sz)
{
	size_t	src_sz;
	size_t	i;

	src_sz = ft_strlen(src);
	i = 0;
	if (sz != 0)
	{
		while (src[i] && i < (sz -1))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (src_sz);
}
