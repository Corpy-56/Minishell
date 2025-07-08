/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:27:42 by skuor             #+#    #+#             */
/*   Updated: 2025/05/06 11:52:23 by skuor            ###   ########.fr       */
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
