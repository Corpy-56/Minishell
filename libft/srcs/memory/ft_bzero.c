/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:38:13 by skuor             #+#    #+#             */
/*   Updated: 2024/12/04 12:02:40 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h" 

void	ft_bzero(void *s, size_t n)
{
	size_t	t;
	char	*str;

	t = 0;
	str = (char *)s;
	while (t < n)
	{
		str[t] = 0;
		t++;
	}
}
/*
#include <stdio.h>
int     main()
{
        char    str[] = "bojojdwndwen";
        size_t  t;

        t = 4;
        printf("%s\n", str);
        ft_bzero(str, t);
        printf("%c\n", str[2]);
        return 0;

}
*/
