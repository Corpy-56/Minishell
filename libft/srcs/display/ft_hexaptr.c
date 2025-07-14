/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexaptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 09:27:53 by skuor             #+#    #+#             */
/*   Updated: 2025/07/14 19:45:58 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	size_n(unsigned long int n)
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

int	ft_hexaptr(unsigned long int n)
{
	int		count;

	if (!n)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	count = size_n(n);
	write(1, "0x", 2);
	ft_puthexptr(n);
	return (count + 2);
}

void	ft_puthexptr(unsigned long int nb)
{
	if (nb > 15)
	{
		ft_puthexptr(nb / 16);
		ft_puthexptr(nb % 16);
	}
	if (nb <= 9)
		ft_putchar(nb + 48);
	if (nb >= 10 && nb <= 15)
		ft_putchar(nb + 87);
}

/* int	main()
{
	ft_hexaptr(4565);
	printf("\n%p", 4565);
} */