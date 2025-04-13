/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 02:18:17 by lfirmin           #+#    #+#             */
/*   Updated: 2024/05/30 18:36:18 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dsts)
{
	size_t	srcs;
	size_t	i;

	ft_strlen(src);
	if (!src || !dst)
		return (0);
	srcs = ft_strlen(src);
	i = 0;
	if (dsts != 0)
	{
		while (src[i] != '\0' && i < (dsts - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (srcs);
}
