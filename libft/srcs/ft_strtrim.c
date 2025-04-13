/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 21:32:01 by lfirmin           #+#    #+#             */
/*   Updated: 2024/05/31 02:04:11 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
		{
			return (1);
		}
		set++;
	}
	return (0);
}

static char	*ft_strncpy(char *dest, const char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		++i;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	s;
	size_t	e;
	size_t	len;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	s = 0;
	while (s1[s] && is_in_set(s1[s], set))
		s++;
	e = ft_strlen(s1);
	while (e > s && is_in_set(s1[e - 1], set))
		e--;
	len = e - s;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	ft_strncpy(str, s1 + s, len);
	str[len] = '\0';
	return (str);
}
