/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:15:46 by skuor             #+#    #+#             */
/*   Updated: 2025/02/12 15:01:49 by skuor            ###   ########.fr       */
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
		res = ft_strjoin(res, buf);
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
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (res[i] && res[i] != '\n')
		i++;
	if (res[i] == '\n')
		i++;
	str = ft_calloc(sizeof(char), (ft_strlen(res) - i + 1));
	if (!str)
		return (NULL);
	j = 0;
	while (res[i])
	{
		str[j] = res[i];
		i++;
		j++;
	}
	free(res);
	return (str);
}

char	*get_next_line(int fd)
{
	char			*str;
	static char		*temp[1025];

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(temp[fd]);
		temp[fd] = NULL;
		return (NULL);
	}
	temp[fd] = ft_read(fd, temp[fd]);
	if (!temp[fd])
	{
		free(temp[fd]);
		temp[fd] = NULL;
		return (NULL);
	}
	str = ft_line(temp[fd]);
	temp[fd] = ft_next(temp[fd]);
	return (str);
}
