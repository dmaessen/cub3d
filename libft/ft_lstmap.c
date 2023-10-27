/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:39:49 by dmaessen          #+#    #+#             */
/*   Updated: 2022/11/03 12:08:33 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*current;
	t_list	*start_lst;
	t_list	*new_lst;

	start_lst = NULL;
	current = lst;
	while (current != NULL)
	{
		new_lst = ft_lstnew(f(current->content));
		if (new_lst == NULL)
		{
			ft_lstclear(&start_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&start_lst, new_lst);
		current = current->next;
	}
	return (start_lst);
}
