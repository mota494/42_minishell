/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloureir <mloureir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:49:10 by mloureir          #+#    #+#             */
/*   Updated: 2023/10/12 12:50:23 by mloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*newlt(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	void	*cont;

	if (!lst || !f || !del)
		return (NULL);
	cont = f(lst->content);
	newlist = ft_lstnew(cont);
	if (!newlist)
	{
		del(cont);
		return (NULL);
	}
	return (newlist);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*savelst;
	void	*cont;

	newlist = newlt(lst, f, del);
	if (!newlist)
		return (NULL);
	savelst = newlist;
	lst = lst->next;
	while (lst)
	{
		cont = f(lst->content);
		savelst->next = ft_lstnew(cont);
		if (!savelst->next)
		{
			del(cont);
			ft_lstclear(&newlist, del);
			return (NULL);
		}
		savelst = savelst->next;
		savelst->next = NULL;
		lst = lst->next;
	}
	return (newlist);
}
