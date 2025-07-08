/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:26:33 by skuor             #+#    #+#             */
/*   Updated: 2024/11/28 15:07:38 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write (fd, &s[i], 1);
		i++;
	}
	write (fd, "\n", 1);
}
/*
#include <fcntl.h>
int	main()
{
	int	fd;

	fd = open("putendl.txt", O_RDWR | O_TRUNC | O_CREAT, 0640);
	if (fd == -1)
		return 1;
	ft_putendl_fd("ffdfd", fd);
	ft_putendl_fd("ffdfd", fd);
	close(fd);
	return 0;
}
*/
