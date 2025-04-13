/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:14:02 by lfirmin           #+#    #+#             */
/*   Updated: 2024/06/03 18:15:05 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t c, size_t s)
{
	void			*ptr;
	long long int	tmp1;
	long long int	tmp2;

	tmp1 = (long long int)c;
	tmp2 = (long long int)s;
	if ((c > 4294967295 || s > 4294967295) && (tmp1 < 0 && tmp2 < 0))
		return (NULL);
	if (tmp1 * tmp2 < 0)
		return (NULL);
	ptr = malloc(c * s);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, c * s);
	return (ptr);
}
