/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 05:56:37 by lfirmin           #+#    #+#             */
/*   Updated: 2024/06/04 12:08:51 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_c(char const *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			count++;
		i++;
	}
	return (count);
}

void	init_split_struct(t_split_struct *v, char const *s, char c)
{
	if (!s)
		return ;
	v->array = (char **)malloc((ft_c(s, c) + 1) * sizeof(char *));
	if (!s || !v->array)
		return ;
	v->i = 0;
	v->j = 0;
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

char	**free_split(char **array, size_t j)
{
	while (j > 0)
	{
		free(array[--j]);
	}
	free(array);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	t_split_struct	v;

	init_split_struct(&v, s, c);
	if (!s || !v.array)
		return (NULL);
	while (s[v.i])
	{
		while (s[v.i] == c && s[v.i])
			v.i++;
		v.start = v.i;
		while (s[v.i] != c && s[v.i])
			v.i++;
		if (v.i > v.start)
		{
			v.array[v.j] = (char *)malloc(v.i - v.start + 1);
			if (!v.array[v.j])
				return (free_split(v.array, v.j));
			ft_strncpy(v.array[v.j], &s[v.start], v.i - v.start);
			v.array[v.j][v.i - v.start] = '\0';
			v.j++;
		}
	}
	v.array[v.j] = NULL;
	return (v.array);
}
