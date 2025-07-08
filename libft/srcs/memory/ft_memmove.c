/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:57:04 by skuor             #+#    #+#             */
/*   Updated: 2025/05/05 11:34:28 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	t;

	t = 0;
	if (src == NULL && dest == NULL)
		return (NULL);
	if (src > dest)
	{
		while (t != n)
		{	
			((char *)dest)[t] = ((char *)src)[t];
			t++;
		}
	}
	else
	{
		while (n > 0)
		{
			((char *)dest)[n - 1] = ((char *)src)[n - 1];
			n--;
		}
	}
	return (dest);
}
