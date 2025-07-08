/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:36:49 by skuor             #+#    #+#             */
/*   Updated: 2024/11/28 12:05:48 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	t;
	char	*d;
	char	*s;

	t = 0;
	d = (char *)dest;
	s = (char *)src;
	if (d == 0 && s == 0)
		return (dest);
	while (t != n)
	{
		d[t] = s[t];
		t++;
	}
	return (dest);
}
/*
#include <string.h>
int	main()
{
	char	dest[] = "";
	char	src[] = "";
	size_t	t;

	t = 13;
	printf("Avant : %s\n", dest);
//	memcpy(dest, src, t);
	ft_memcpy(dest, src, t);
	printf("Apres : %s\n", dest);

	return 0;
}
*/
