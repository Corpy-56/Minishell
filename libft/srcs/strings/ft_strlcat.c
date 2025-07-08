/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:20:33 by skuor             #+#    #+#             */
/*   Updated: 2024/12/04 12:07:43 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	t;
	size_t	s;
	size_t	u;

	t = 0;
	s = 0;
	while (dst[t])
		t++;
	dst[t] = '\0';
	while (src[s])
		s++;
	u = 0;
	if (siz > 0)
	{
		while (src[u] && (t + u) < (siz - 1))
		{	
			dst[t + u] = src[u];
			u++;
		}
		dst[t + u] = '\0';
	}
	if ((siz <= t && src[u] != '\0') || siz <= t)
		return (siz + s);
	return (t + s);
}
/*
#include <stdio.h>
#include <bsd/string.h>
int	main()
{
	char    src[] = "lorem ipsum dolor sit amet";
        char    dst[10] = "a";
        size_t  t;


	t = 0;
	printf("%zu\n", ft_strlcat(dst, src, t));
//	printf("%zu\n", strlcat(dst, src, t));
	printf("%s\n", dst);

	return 0;
}
*/
