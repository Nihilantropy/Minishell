/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:01:52 by crea              #+#    #+#             */
/*   Updated: 2024/02/05 14:43:16 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t sz)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (sz == 0)
		return (ft_strlen(src));
	while (dest[i] && i < sz)
		i++;
	while ((i + j + 1) < sz && src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	if (i != sz)
		dest[i + j] = '\0';
	return (i + ft_strlen(src));
}
