/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 06:42:38 by lfirmin           #+#    #+#             */
/*   Updated: 2024/05/30 18:30:00 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	i;
	int	last_occurrence;

	ft_strlen(str);
	i = 0;
	last_occurrence = -1;
	if (str == NULL)
		return (NULL);
	while (str[i])
	{
		if (str[i] == (char)c)
			last_occurrence = i;
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&str[i]);
	if (last_occurrence != -1)
		return ((char *)&str[last_occurrence]);
	return (NULL);
}
