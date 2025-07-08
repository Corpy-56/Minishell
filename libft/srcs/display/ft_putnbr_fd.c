/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:43:16 by skuor             #+#    #+#             */
/*   Updated: 2024/12/04 12:07:00 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write (fd, "-2147483648", 11);
		return ;
	}
	if (n >= 0 && n <= 9)
		ft_putchar_fd(n + 48, fd);
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd((n * -1), fd);
	}
	if (n > 9)
	{
		ft_putnbr_fd((n / 10), fd);
		ft_putnbr_fd((n % 10), fd);
	}
}
/*
#include <fcntl.h>
int	main()
{
	int	n;
	int	fd;

	n = -2147483648;
	fd = open("putnbr.txt", O_WRONLY | O_TRUNC | O_CREAT, 0640);
	if (fd == -1)
		return 1;
	ft_putnbr_fd(n, fd);
	close(fd);
	return 0;

}
*/
