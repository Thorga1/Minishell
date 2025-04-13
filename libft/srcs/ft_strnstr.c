/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 08:22:59 by lfirmin           #+#    #+#             */
/*   Updated: 2024/05/22 09:59:44 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *hay, const char *need, size_t len)
{
	size_t	i;
	size_t	n;

	i = 0;
	if (need[0] == '\0')
		return ((char *)hay);
	while (hay[i] != '\0')
	{
		n = 0;
		while (hay[i + n] == need[n] && (i + n) < len)
		{
			if (hay[i + n] == '\0' && need[n] == '\0')
				return ((char *)&hay[i]);
			n++;
		}
		if (need[n] == '\0')
			return ((char *)hay + i);
		i++;
	}
	return (0);
}
