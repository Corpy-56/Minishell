/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 15:23:24 by skuor             #+#    #+#             */
/*   Updated: 2025/10/12 17:09:43 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_nodes(t_env *list)
{
	int	count;

	count = 0;
	while (list)
	{
		count++;
		list = list->next;
	}
	return (count);
}

// int	ft_quote(char *rl)
// {
// 	size_t	i;

// 	i = 0;
// 	while (rl[i])
// 	{
// 		if (rl[i] == '\'')
// 		{
// 			i++;
// 			while (rl[i] && rl[i] != '\'')
// 				i++;
// 			if (rl[i] == '\0')
// 				return (1);
// 		}
// 		else if (rl[i] == '\"')
// 		{
// 			i++;
// 			while (rl[i] && rl[i] != '\"')
// 				i++;
// 			if (rl[i] == '\0')
// 				return (1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// int	ft_quote(char *rl, int i)
// {
// 	int	quote1;

// 	quote1 = 0;
// 	while (rl[i])
// 	{
// 		if (quote1 == 0 && rl[i] == '\'')
// 		{
// 			i++;
// 			while (rl[i] != '\'' && rl[i])
// 				i++;
// 			if (rl[i] == '\0')
// 				quote1++;
// 		}
// 		else if (quote1 == 0 && rl[i] == '\"')
// 		{
// 			i++;
// 			while (rl[i] != '\"' && rl[i])
// 				i++;
// 			if (rl[i] == '\0')
// 				quote1++;
// 		}
// 		i++;
// 	}
// 	if (quote1 != 0)
// 		return (ft_error(1, "Problem with quote\n", NULL));
// 	return (0);
// }

int	ft_quote(char *rl, int i)
{
	int		quote1;
	char	q;

	quote1 = 0;
	q = 0;
	while (rl[i])
	{
		if (quote1 == 0 && (rl[i] == '\'' || rl[i] == '\"'))
		{
			q = rl[i];
			i++;
			while (rl[i] != '\'' && rl[i] != q)
				i++;
			if (rl[i] == '\0')
				quote1++;
		}
		i++;
	}
	if (quote1 != 0)
		return (ft_error(1, "Problem with quote\n", NULL));
	return (0);
}

char	*ft_strjoin_char(char *str, const char c)
{
	int		i;
	char	*joined;

	if (str == NULL)
	{
		joined = ft_calloc(2, 1);
		if (joined == NULL)
			return (NULL);
		joined[0] = c;
		joined[1] = '\0';
		return (joined);
	}
	joined = ft_calloc(ft_strlen(str) + 2, 1);
	if (joined == NULL)
	{
		free(str);
		return (NULL);
	}
	i = -1;
	while (str[++i])
		joined[i] = str[i];
	joined[i++] = c;
	joined[i] = '\0';
	free(str);
	return (joined);
}

int	white_space(char *str, int i)
{
	while (str[i] != '\0' && (str[i] == 32 || str[i] == 9))
	{
		if (i != 0 && str[i] == '$' && (str[i - 1] != 32 || str[i - 1] != 9))
			i++;
		i++;
	}
	if (str[i] != 32 && str[i] != 9 && str[i] != '\0')
		return (i);
	else if (str[i] == '\0')
		return (-1);
	return (0);
}
