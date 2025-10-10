/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:15:46 by skuor             #+#    #+#             */
/*   Updated: 2025/10/10 17:08:13 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_read(int fd, char *res)
{
	char		*buf;
	size_t		nbytes;

	if (!res)
		res = ft_calloc(1, 1);
	buf = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	nbytes = 1;
	while (!ft_strchr(buf, '\n') && nbytes > 0)
	{
		nbytes = read(fd, buf, BUFFER_SIZE);
		buf[nbytes] = 0;
		res = ft_strjoin_free(res, buf);
	}
	free(buf);
	if (*res)
		return (res);
	free(res);
	return (NULL);
}

char	*ft_line(char *res)
{
	char	*str;
	int		i;

	i = 0;
	while (res[i] && res[i != '\n'])
		i++;
	if (res[i] == '\n')
		i++;
	str = ft_calloc(sizeof(char), i + 2);
	if (!str)
		return (NULL);
	i = 0;
	while (res[i] && res[i] != '\n')
	{
		str[i] = res[i];
		i++;
	}
	if (res[i] == '\n')
	{
		str[i] = res[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_next(char *res)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (res[i] && res[i] != '\n')
		i++;
	if (res[i])
		i++;
	while (res[i])
	{
		res[j] = res[i];
		i++;
		j++;
	}
	res[j] = 0;
	return (res);
}

static void	free_gnl(char *tmp[1025])
{
	int	i;

	i = 0;
	while (i < 1025)
	{
		free(tmp[i]);
		tmp[i] = NULL;
		i++;
	}
}

char	*get_next_line(int fd)
{
	char			*str;
	static char		*tmp[1025];

	if (fd == -1)
	{
		free_gnl(tmp);
		return (NULL);
	}
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(tmp[fd]);
		tmp[fd] = NULL;
		return (NULL);
	}
	tmp[fd] = ft_read(fd, tmp[fd]);
	if (!tmp[fd])
	{
		free(tmp[fd]);
		tmp[fd] = NULL;
		return (NULL);
	}
	str = ft_line(tmp[fd]);
	tmp[fd] = ft_next(tmp[fd]);
	return (str);
}
