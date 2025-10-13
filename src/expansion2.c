/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:16:15 by skuor             #+#    #+#             */
/*   Updated: 2025/10/13 10:37:07 by skuor            ###   ########.fr       */
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
	char	*name;
	char	*value;
	char	*dup;

	start = i;
	len_str = ft_strlen(args);
	while (i < len_str && (ft_isalnum(args[i]) || args[i] == '_'))
		i++;
	if (i == start)
		i_equal_start(str, &start);
	name = ft_substr(args, start, i - start);
	value = get_env_value(stru->environ, name);
	if (!value && stru->local)
		value = get_env_value(stru->local, name);
	if (value)
		dup = ft_strdup(value);
	else
		dup = ft_strdup("");
	if (!dup)
		return (free(name), start);
	if (append_str(str, dup) < 0)
		return (free_dup_name(dup, name), start);
	return (free_dup_name(dup, name), i);
}

void	main_expand(t_shell *stru)
{
	t_tokens	*token;
	char		*expanded;

	token = stru->tokens;
	while (token)
	{
		if (token->str == NULL)
			token = token->next;
		else if (ft_strncmp(token->str, "<<", 3) == 0 && token->next != NULL)
		{
			token = token->next;
			while (token->str == NULL && token->next != NULL)
				token = token->next;
			token = token->next;
		}
		else
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
}

