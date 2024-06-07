/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:07:03 by crea              #+#    #+#             */
/*   Updated: 2024/02/05 14:43:16 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_substr(const char *str, unsigned int start, size_t len)
{
	char	*sub_str;

	if (!str)
		return (0);
	if (start >= ft_strlen(str))
		return (ft_strdup(""));
	if (ft_strlen(str) < start)
		len = 0;
	if (ft_strlen(str + start) < len)
		len = ft_strlen(str + start);
	sub_str = malloc(sizeof(char) * (len + 1));
	if (!sub_str)
		return (0);
	ft_strlcpy(sub_str, str + start, len + 1);
	return (sub_str);
}
