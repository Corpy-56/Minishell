/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:54:18 by skuor             #+#    #+#             */
/*   Updated: 2024/11/27 17:38:29 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int					i;
	char				*str;
	unsigned int		nc;

	i = 0;
	nc = (unsigned char)c;
	str = (char *)s;
	while (s[i])
	{
		if ((unsigned char)s[i] == nc)
			return (&str[i]);
		i++;
	}
	if ((unsigned char)s[i] == nc)
		return (&str[i]);
	return (0);
}
/*
#include <stdio.h>
#include <string.h>
int	main()
{
	char *src = "there is so \0ma\0ny \0 \\0 in t\0his stri\0ng !\0\0\0\0";

//	printf("%s\n", strchr(src, '\0'));
	printf("%s\n", ft_strchr(src, '\0'));
	return 0;
}
*/
