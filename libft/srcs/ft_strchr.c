/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:59:37 by crea              #+#    #+#             */
/*   Updated: 2024/02/05 14:43:16 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	if (c == 0)
		return ((char *)str + ft_strlen(str));
	while (str[i])
	{
		if (str[i] == (const char)c)
			return ((char *)str + i);
		i++;
	}
	return (NULL);
}
