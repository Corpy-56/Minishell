/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:49:46 by skuor             #+#    #+#             */
/*   Updated: 2025/09/23 15:16:49 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_quote(char quote)
{
	if (quote == '\'' || quote == '\"')
		return (true);
	return (false);
}

void	skip_quoted(const char *str, size_t *i)
{
	char	quote;
	
	quote = str[*i];
	(*i)++;
	while (str[*i])
	{
		if (str[*i] == quote)
		{
			(*i)++;
			break ;
		}
		(*i)++;
	}
}

char	*remove_quotes(const char *str)
{
	size_t	i;
	size_t	j;
	char	*res;
	char	quote;

	i = 0;
	j = 0;
	res = ft_calloc(ft_strlen(str) + 1, 1);
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
			{
				res[j] = str[i];
				j++;
				i++;
			}
			if (str[i] == quote)
				i++;
		}
		else
		{
			res[j] = str[i];
			j++;
			i++;
		}
	}
	res[j] = '\0';
	return (res);
}

void	unquote_tokens(t_tokens *head)
{
	char	*tmp;
	
	while (head)
	{
		if (head->str)
		{
			tmp = remove_quotes(head->str);	
			if (tmp)
			{
				free(head->str);
				head->str = tmp;
			}
		}
		head = head->next;
	}
}