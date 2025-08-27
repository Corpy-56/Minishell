/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:16:15 by skuor             #+#    #+#             */
/*   Updated: 2025/08/27 18:42:20 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_env *env, char *name)
{
	t_env	*current;

	if (!env || !name)
		return (NULL);
	current = env;
	while (current)
	{
		if (!current->name)
			return (NULL);
		if (ft_strcmp(current->name, name) == 0)
		{
			if (current->value)
				return (ft_strdup(current->value));
			else
				return (ft_strdup(""));
		}
		current = current->next;
	}
	return (NULL);
}
char	*expand_var(char *args, t_shell *stru)
{
	size_t	i;
	size_t	start;
	char	*str;
	char	*name;
	char	*value;
	size_t	len_str;
	char tmp[2];
	char	*status_str;

	i = 0;
	str = ft_strdup("");
	len_str = ft_strlen(args);
	while (i < len_str)
	{
		if (args[i] != '$')
		{
			tmp[0] = args[i];
			tmp[1] = '\0';
			str = ft_strjoin_free(str, ft_strdup(tmp));
			i++;
			continue ;
		}
		if (i + 1 < len_str && args[i + 1] == '?')
		{
			status_str = ft_itoa(stru->last_status);
			str = ft_strjoin_free(str, status_str);
			i += 2;
			continue ;
		}
		i++;
		start = i;
		while ((i < len_str && ft_isalnum(args[i])) || args[i] == '_')
			i++;
		if (i == start)
		{
			str = ft_strjoin_free(str, ft_strdup("$"));
			continue ;
		}
		name = ft_substr(args, start, i - start);
		value = get_env_value(stru->environ, name);
		if (!value && stru->local)
			value = get_env_value(stru->local, name);
		if (!value)
			value = ft_strdup("");
		str = ft_strjoin_free(str, value);
		free(name);
	}
	return (str);
}

void	main_expand(t_shell *stru)
{
	char	*expanded;
	int		j;

	j = 0;
	while (stru->tokens->args[j])
	{
		expanded = expand_var(stru->tokens->args[j], stru);
		if (expanded != stru->tokens->args[j])
			free(stru->tokens->args[j]);
		stru->tokens->args[j] = expanded;
		j++;
	}
}