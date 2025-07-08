/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:01:34 by skuor             #+#    #+#             */
/*   Updated: 2025/02/12 09:59:43 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_unsigned_putnbr(unsigned int nb)
{
	if (nb >= 0 && nb <= 9)
		ft_putchar(nb + 48);
	if (nb > 9)
	{
		ft_unsigned_putnbr(nb / 10);
		ft_unsigned_putnbr(nb % 10);
	}
}

int	ft_putnbr_u(unsigned int nb)
{
	int	i;

	i = 1;
	ft_unsigned_putnbr(nb);
	while (nb > 9)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}
