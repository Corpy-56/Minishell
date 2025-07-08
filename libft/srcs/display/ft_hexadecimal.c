/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexadecimal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:14:00 by skuor             #+#    #+#             */
/*   Updated: 2025/02/12 09:59:17 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	size_n(unsigned int n)
{
	int	count;

	count = 0;
	if (n == 0)
		count++;
	while (n != 0)
	{
		n = n / 16;
		count++;
	}
	return (count);
}

void	ft_puthex(unsigned int nb, char s)
{
	if (nb > 15)
	{
		ft_puthex(nb / 16, s);
		ft_puthex(nb % 16, s);
	}
	if (nb >= 0 && nb <= 9)
		ft_putchar(nb + 48);
	if (nb >= 10 && nb <= 15 && s == 'x')
		ft_putchar(nb + 87);
	if (nb >= 10 && nb <= 15 && s == 'X')
		ft_putchar(nb + 55);
}

int	ft_hexa(unsigned int n, char s)
{
	int		count;

	count = size_n(n);
	ft_puthex(n, s);
	return (count);
}

/* int	main()
{
	ft_hexa(45469,'X');
	printf("\n%X",45469);
} */