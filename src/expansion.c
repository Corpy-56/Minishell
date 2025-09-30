/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:16:15 by skuor             #+#    #+#             */
/*   Updated: 2025/09/30 15:25:01 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_dup_name(char *dup, char *name)
{
	free(dup);
	free(name);
}

size_t	expand_var2(t_shell *stru, char *args, size_t i, char **str)
{
	size_t	start;
	size_t	len_str;

	auto char *name, *value, *dup;
	start = i;
	len_str = ft_strlen(args);
	while (i < len_str && (ft_isalnum(args[i]) || args[i] == '_'))
		i++;
	if (i == start)
	{
		if (append_char(str, '$') < 0)
			return (start);
		return (start);
	}
	name = ft_substr(args, start, i - start);
	value = get_env_value(stru->environ, name);
	if (!value && stru->local)
		value = get_env_value(stru->local, name);
	if (value)
		dup = ft_strdup(value);
	else
		dup = ft_strdup("");
	if (!dup)
		return (free(value), start);
	if (append_str(str, value) < 0)
		return (free_dup_name(dup, name), start);
	return (free_dup_name(dup, name), i);
}

static void	expand_exit_status(t_shell *stru, char **str)
{
	char	*status_str;

	status_str = ft_itoa(stru->last_status);
	append_str(str, status_str);
	free(status_str);
}

char	*expand_var(t_tokens *token, t_shell *stru, size_t i)
{
	char	*str;
	size_t	len_str;
	size_t	start;
	size_t	j;

	str = ft_calloc(1, 1);
	if (!str)
		return (NULL);
	len_str = ft_strlen(token->str);
	start = i;
	while (i < len_str)
	{
		if (token->str[i] == '$' && token->dollars >= 1)
		{
			j = start;
			while (j < i)
			{
				if (append_char(&str, token->str[j]) < 0)
				{
					free(str);
					return (NULL);
				}
				j++;
			}
			if (i + 1 < len_str && token->str[i + 1] == '?')
			{
				expand_exit_status(stru, &str);
				i += 2;
			}
			else
				i = expand_var2(stru, token->str, i + 1, &str);
			start = i;
		}
		else
			i++;
	}
	j = start;
	while (j < i)
	{
		if (append_char(&str, token->str[j]) < 0)
		{
			free(str);
			return (NULL);
		}
		j++;
	}
	return (str);
}

void	main_expand(t_shell *stru)
{
	t_tokens	*token;
	char		*expanded;

	token = stru->tokens;
	while (token)
	{
		expanded = expand_var(token, stru, 0);
		if (expanded)
		{
			free(token->str);
			token->str = expanded;
		}
		token = token->next;
	}
}
