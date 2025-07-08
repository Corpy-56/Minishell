/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:49:03 by skuor             #+#    #+#             */
/*   Updated: 2024/12/04 12:08:45 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		s;
	size_t		t;
	char		*str;

	s = 0;
	t = 0;
	str = (char *)big;
	if (little[t] == '\0')
		return (&str[s]);
	while (big[s] && s < len)
	{
		t = 0;
		while (big[s + t] && big[s + t] == little[t] && s + t < len)
			t++;
		if (little[t] == '\0')
			return (&str[s]);
		s++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <bsd/string.h>
int	main()
{
	char	big[] = "If little is an empty string, lis is returned; 
	if little occurs nowhere in big, NULL is returned";
	char	little[] = "oh";
	size_t	s;

	s = 100;
	printf("%s\n", strnstr(big, little, s));
	printf("%s\n", ft_strnstr(big, little, s));
	return 0;
}
*/
