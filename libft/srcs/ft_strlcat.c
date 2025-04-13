/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 03:55:25 by lfirmin           #+#    #+#             */
/*   Updated: 2024/05/22 09:59:44 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	r;
	size_t	s;

	i = 0;
	r = ft_strlen(dst);
	s = ft_strlen(src);
	if (size <= r)
		return (s + size);
	while (r + i < size - 1 && src[i] != '\0')
	{
		dst[r + i] = src[i];
		i++;
	}
	dst[r + i] = '\0';
	return (r + s);
}
