/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 20:02:19 by crea              #+#    #+#             */
/*   Updated: 2024/02/05 14:40:20 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	getdigits(long int n)
{
	int	digits;

	digits = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		digits++;
	}
	while (n > 0)
	{
		digits++;
		n /= 10;
	}
	return (digits);
}

char	*ft_itoa(int n)
{
	char		*digit_str;
	int			digits;
	int			j;
	long int	nb;

	nb = (long int)n;
	digits = getdigits(nb);
	digit_str = (char *)malloc(digits + 1);
	j = -1;
	if (!digit_str)
		return (NULL);
	digit_str[digits--] = '\0';
	if (nb < 0)
	{
		nb *= -1;
		digit_str[0] = '-';
		j = 0;
	}
	while (digits > j)
	{
		digit_str[digits] = (nb % 10) + '0';
		nb = nb / 10;
		digits--;
	}
	return (digit_str);
}
