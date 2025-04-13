/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:21:09 by lfirmin           #+#    #+#             */
/*   Updated: 2024/06/03 15:53:13 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*save;

	if (!lst || !del || !f)
		return (NULL);
	new = ft_lstnew(lst->content);
	if (!new)
		return (NULL);
	new->content = f(new->content);
	save = new;
	lst = lst->next;
	while (lst)
	{
		new->next = ft_lstnew(lst->content);
		if (!new->next)
		{
			ft_lstclear(&save, del);
			return (NULL);
		}
		new->next->content = f(new->next->content);
		new = new->next;
		lst = lst->next;
	}
	new->next = NULL;
	return (save);
}
