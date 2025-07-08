/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:34:44 by skuor             #+#    #+#             */
/*   Updated: 2025/02/11 15:38:05 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*elmt;

	while (*lst)
	{	
		elmt = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = elmt;
	}
	lst = (NULL);
}
