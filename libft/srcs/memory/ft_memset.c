/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:07:13 by skuor             #+#    #+#             */
/*   Updated: 2024/12/04 12:06:24 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*str;
	size_t	i;

	str = (char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	return (s);
}
/*
#include <stdio.h>
int	main()
{
	char	str[] = "bojojdwndwen";
	int	i;
	size_t	t;

	i = '5';
	t = 4;
	printf("%p\n", str);
	ft_memset(str, i, t);
	printf("%p\n", str);
	return 0;

}
*/
