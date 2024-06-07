/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:01:42 by crea              #+#    #+#             */
/*   Updated: 2024/02/05 14:43:16 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*str_join;
	size_t	sz_join;
	size_t	i;

	sz_join = ft_strlen(s1) + ft_strlen(s2) + 1;
	str_join = (char *)malloc(sz_join);
	if (!str_join)
		return (0);
	i = 0;
	while (*s1)
		str_join[i++] = *s1++;
	while (*s2)
		str_join[i++] = *s2++;
	str_join[i] = '\0';
	return (str_join);
}
