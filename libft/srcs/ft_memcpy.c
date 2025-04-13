/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 01:08:31 by lfirmin           #+#    #+#             */
/*   Updated: 2024/05/30 18:46:00 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*r;
	unsigned char	*s;

	i = 0;
	r = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (dest == (void *)0 && src == (void *)0)
		return (dest);
	while (i < len)
	{
		r[i] = s[i];
		i++;
	}
	return (dest);
}
