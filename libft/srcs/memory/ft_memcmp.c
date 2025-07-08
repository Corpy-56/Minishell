/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:27:42 by skuor             #+#    #+#             */
/*   Updated: 2024/11/28 14:49:31 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			t;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	t = 0;
	if (n == 0)
		return (0);
	while (t < n - 1)
	{
		if (str1[t] != str2[t])
			return (str1[t] - str2[t]);
		t++;
	}
	return (str1[t] - str2[t]);
}
/*
#include <string.h>
int	main()
{
	char	s1[] = "\xff\0\0\xaa\0\xde\xffMACOSX\xff";
	char	s2[] = "\xff\0\0\xaa\0\xde\x00MBS";
	size_t	n;

	n = 0;
	printf("%d\n", memcmp(s1, s2, n));
	printf("%d\n", ft_memcmp(s1, s2, n));
	return 0;
}
*/
