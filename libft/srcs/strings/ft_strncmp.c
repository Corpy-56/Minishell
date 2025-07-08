/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:10:09 by skuor             #+#    #+#             */
/*   Updated: 2024/12/04 12:08:10 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	t;

	t = 0;
	while ((s1[t] && t < n) || (s2[t] && t < n))
	{
		if ((s1[t] > s2[t] || s1[t] < s2[t]))
			return ((unsigned char)s1[t] - (unsigned char)s2[t]);
		t++;
	}
	return (0);
}
/*
#include <stdio.h>
int	main()
{
	char	s1[] = "ABAJUBC";
	char	s2[] = "ABZCTJ";
	size_t	i;

	i = 3;
	printf("%d\n", ft_strncmp(s1, s2, i));
	return 0;
}
*/
