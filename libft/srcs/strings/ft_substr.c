/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:46:49 by skuor             #+#    #+#             */
/*   Updated: 2024/11/28 11:49:31 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	size_m(char const *s, unsigned int start, size_t len)
{
	size_t	j;

	if (ft_strlen(s) <= start || len == 0)
		j = 0;
	if (ft_strlen(s) > start)
		j = ft_strlen(s) - start;
	if (ft_strlen(s) > start && len < j)
		j = len;
	return (j);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	size_t			j;
	unsigned int	i;

	i = 0;
	j = size_m(s, start, len);
	str = malloc(sizeof(char) * (j + 1));
	if (!str)
		return (0);
	if (start >= ft_strlen(s) || !s)
	{
		str[i] = '\0';
		return (str);
	}
	while (s[i] && i < len)
	{
		str[i] = (char)s[i + start];
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*
#include <stdio.h>
int	main()
{
	char	str[] = "01234";
	unsigned int	i;
	size_t	t;

	i = 0;
	t = 10;

	printf("%s\n", ft_substr(str, i, t));
	return 0;
}
*/
