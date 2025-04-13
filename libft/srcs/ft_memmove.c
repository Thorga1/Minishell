/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmov.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 01:26:13 by lfirmin           #+#    #+#             */
/*   Updated: 2024/05/22 09:59:44 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *s1, const void *s2, size_t len)
{
	unsigned char	*dest;
	unsigned char	*src;
	unsigned int	i;

	dest = (unsigned char *)s1;
	src = (unsigned char *)s2;
	i = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (dest < src)
	{
		while (i < len)
		{
			dest[i] = src[i];
			i++;
		}
	}
	else
	{
		while (0 < len--)
			dest[len] = src[len];
	}
	return (dest);
}
