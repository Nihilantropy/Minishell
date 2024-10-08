/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:00:42 by crea              #+#    #+#             */
/*   Updated: 2024/02/05 14:43:16 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strdup(const char *str)
{
	size_t	dup_sz;
	char	*dup_str;

	if (!str)
		return (NULL);
	dup_sz = ft_strlen(str);
	dup_str = (char *)malloc(dup_sz + 1);
	if (!dup_str)
		return (NULL);
	ft_memcpy(dup_str, str, (dup_sz + 1));
	return (dup_str);
}
