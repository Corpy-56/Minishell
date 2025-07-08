/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:58:02 by skuor             #+#    #+#             */
/*   Updated: 2024/11/27 10:55:09 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t siz)
{
	size_t	t;

	t = 0;
	if (siz > 0)
	{
		while (src[t] && t < (siz - 1))
		{
			dst[t] = src[t];
			t++;
		}
		dst[t] = '\0';
	}
	while (src[t])
		t++;
	return (t);
}
/*
#include <bsd/string.h>
#include <stdio.h>
int	main()
{
	char	src[] = "lorem ipsum dolor sit amet";
	char	dst[10] = "a";
	size_t	t;

	t = 0;
//	strlcpy(dst, src, t);
	printf("Apres : %zu\n", ft_strlcpy(dst, src, t));
	write(1, dst, 15);

	return 0;
}
*/
