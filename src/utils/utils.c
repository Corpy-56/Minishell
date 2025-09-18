/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarah <sarah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:21:04 by skuor             #+#    #+#             */
/*   Updated: 2025/09/18 10:12:16 by sarah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error(int i, char *str, char *str2)
{
	(void)i;
	if (str2 != NULL)
		write(2, str2, (ft_strlen(str)));
	write(2, str, (ft_strlen(str)));
	return (-1);
}

int	white_space(char *str, int i)
{
	while (str[i] != '\0' && (str[i] == 32 || str[i] == 9))
		i++;
	if (str[i] != 32 && str[i] != 9 && str[i] != '\0')
		return (i);
	else if (str[i] == '\0')
		return (-1);
	return (0);
}

bool	is_local_var(char *s)
{
	int	i;

	if (!s || !s[0])
		return (false);
	if (!(ft_isalpha(s[0]) || s[0] == '_'))
		return (false);
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (!(ft_isalnum((unsigned char)s[i]) || s[i] == '_'))
			return (false);
		i++;
	}
	return (s[i] == '=');
}

int	append_char(char **result, char c)
{
	char	*tmp;

	tmp = ft_strjoin_char(*result, c);
	if (!tmp)
		return (-1);
	*result = tmp;
	return (0);
}

int	append_str(char **result, const char *str)
{
	int		i;
	char	*tmp;
	
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		tmp = ft_strjoin_char(*result, str[i]);
		if (!tmp)
			return (-1);
		i++;
		*result = tmp;
	}
	return (0);
}
