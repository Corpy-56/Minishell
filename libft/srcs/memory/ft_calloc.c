/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:04:33 by skuor             #+#    #+#             */
/*   Updated: 2025/02/12 11:06:52 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t type, size_t nbr)
{
	void	*res;
	size_t	i;
	size_t	bytes;

	bytes = type * nbr;
	if (bytes / nbr != type)
		return (NULL);
	i = 0;
	res = malloc(bytes);
	if (!res)
		return (NULL);
	while (i < bytes)
	{
		((char *)res)[i] = 0;
		i++;
	}
	return (res);
}
/*
int	main()
{
	int	n = 8539;
	int	*array;

	array = (int *)ft_calloc(n, sizeof(int));
	return 0;
}
*/
