/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:45:38 by skuor             #+#    #+#             */
/*   Updated: 2024/12/04 12:09:10 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int					i;
	char				*str;
	unsigned int		nc;

	i = 0;
	nc = (unsigned char)c;
	str = (char *)s;
	while (s[i])
		i++;
	while (i > 0)
	{
		if ((unsigned char)s[i] == nc)
			return (&str[i]);
		i--;
	}
	if ((unsigned char)s[i] == nc)
		return (&str[i]);
	return (0);
}
/*
#include <stdio.h>
int	main()
{
	char	str[] = "The  strchr() function returns a 
	pointer to the first occurrence of the character c in the string s.";
	int	i;

	i = 'a';
	printf("%s\n", ft_strrchr(str, i));
	return 0;
}
*/
