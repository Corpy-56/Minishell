/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 09:19:19 by skuor             #+#    #+#             */
/*   Updated: 2024/11/26 10:00:19 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	size_n(long i)
{
	int	j;

	j = 0;
	if (i == 0)
		j++;
	if (i < 0)
	{
		j = 1;
		i *= -1;
	}
	if (i >= 0)
	{
		while (i)
		{	
			i = i / 10;
			j++;
		}
	}
	return (j);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	l;
	int		i;

	l = n;
	i = size_n(n);
	str = malloc(sizeof(char) * i + 1);
	if (!str)
		return (0);
	str[i] = '\0';
	i--;
	if (l < 0)
	{
		l = -l;
		str[0] = '-';
	}
	while (l / 10 != 0)
	{
		str[i] = (l % 10) + 48;
		l = l / 10;
		i--;
	}
	str[i] = l + 48;
	return (str);
}
/*
#include <stdio.h>
int	main()
{
	int	nb = -2147483648;

	printf("%s\n", ft_itoa(nb));
	return 0;
}
*/
