/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:01:33 by skuor             #+#    #+#             */
/*   Updated: 2024/12/04 12:05:25 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;

	str = (unsigned char *)s;
	while (n > 0)
	{
		if (*str == (unsigned char)c)
			return (str);
		str++;
		n--;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>
int	main()
{
	char str[] = "dewdws";
	char	c;	
	size_t	t;

	c = 'w';
	t = 4;
	printf("%s\n", (char *)memchr(str, c, t));
	printf("%s\n", (char *)ft_memchr(str, c, t));
	return 0;
}
*/
