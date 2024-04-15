/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgreau <lgreau@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 22:08:44 by lgreau            #+#    #+#             */
/*   Updated: 2024/04/14 12:59:21 by lgreau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linked_list.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*elem;
	t_list	*next;

	if (!lst)
		return ;
	elem = *lst;
	while (elem)
	{
		next = elem->next;
		if (del)
			(*del)(elem->content);
		free(elem);
		elem = next;
	}
	*lst = NULL;
}
