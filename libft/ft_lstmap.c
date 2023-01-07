/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 14:08:55 by rapdos-s          #+#    #+#             */
/*   Updated: 2022/07/02 00:52:21 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*content_new;
	t_list	*list_new;

	list_new = NULL;
	if (!lst)
		return (NULL);
	while (lst)
	{
		content_new = ft_lstnew(f(lst->content));
		if (!content_new)
		{
			ft_lstclear(&list_new, del);
			return (NULL);
		}
		ft_lstadd_back(&list_new, content_new);
		lst = lst -> next;
	}
	return (list_new);
}
