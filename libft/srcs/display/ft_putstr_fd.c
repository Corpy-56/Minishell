/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:12:23 by skuor             #+#    #+#             */
/*   Updated: 2024/11/26 13:40:50 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write (fd, &s[i], 1);
		i++;
	}
}
/*
#include <fcntl.h>
int	main()
{
	int	fd;

	fd = open("test.txt", O_RDWR | O_TRUNC | O_CREAT, 0640);
	if (fd == -1)
		return 1;
	ft_putstr_fd("lollolo", fd);
	ft_putstr_fd("ffdfd", fd);
	close(fd);
	return 0;
}
*/
