/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:59:00 by lfirmin           #+#    #+#             */
/*   Updated: 2024/05/29 10:31:36 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static size_t	ft_count(long int n)
{
	size_t	c;

	c = 0;
	if (n <= 0)
		c = 1;
	while (n != 0)
	{
		n = n / 10;
		c++;
	}
	return (c);
}

char	*ft_itoa(int n)
{
	char		*str;
	size_t		size;
	long int	num;

	num = n;
	size = ft_count(num);
	str = (char *)malloc(size + 1);
	if (!str)
		return (NULL);
	str[size] = '\0';
	if (num < 0)
		num = -num;
	while (size--)
	{
		str[size] = num % 10 + '0';
		num = num / 10;
		if (n < 0 && size == 0)
			str[size] = '-';
	}
	return (str);
}
