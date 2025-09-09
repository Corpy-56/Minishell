/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:16:15 by skuor             #+#    #+#             */
/*   Updated: 2025/09/09 15:37:45 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	expand_var2(t_shell *stru, char *args, size_t i, char **str)
{
	size_t	start;
	size_t	len_str;
	char	*name;
	char	*value;

	start = i;
	len_str = ft_strlen(args);
	while (i < len_str && (ft_isalnum(args[i]) || args[i] == '_'))
		i++;
	if (i == start)
	{
		*str = ft_strjoin_free(*str, ft_strdup("$"));
		return (start);
	}
	name = ft_substr(args, start, i - start);
	value = get_env_value(stru->environ, name);
	if (!value && stru->local)
		value = get_env_value(stru->local, name);
	if (!value)
		value = ft_strdup("");
	*str = ft_strjoin_free(*str, value);
	free(name);
	return (i);
}

static void	no_expansion(char *args, char **str, size_t i)
{
	char	tmp[2];

	tmp[0] = args[i];
	tmp[1] = '\0';
	*str = ft_strjoin_free(*str, ft_strdup(tmp));
}

static void	expand_exit_status(t_shell *stru, char **str)
{
	char	*status_str;

	status_str = ft_itoa(stru->last_status);
	*str = ft_strjoin_free(*str, status_str);
}

char	*expand_var(char *args, t_shell *stru)
{
	size_t	i;
	char	*str;
	size_t	len_str;

	i = 0;
	str = ft_strdup("");
	len_str = ft_strlen(args);
	while (i < len_str)
	{
		if (args[i] == '$' && stru->tokens->dollars == 1)
		{
			if (i + 1 < len_str && args[i + 1] == '?')
			{
				expand_exit_status(stru, &str);
				i += 2;
			}
			else
			{
				i++;
				i = expand_var2(stru, args, i, &str);
			}
		}
		else
		{
			// Ajouter le caractère tel quel
			no_expansion(args, &str, i);
			i++;
		}
		// else
		// {
		// 	// Ajouter le caractère tel quel
		// 	char tmp[2] = {args[i], '\0'};
		// 	str = ft_strjoin_free(str, ft_strdup(tmp));
		// 	i++;
		// }
	}
	return (str);
}

// void	main_expand(t_shell *stru)
// {
// 	char	*expanded;
// 	int		j;

// 	j = 0;
// 	while (stru->tokens->args[j])
// 	{
// 		expanded = expand_var(stru->tokens->args[j], stru);
// 		// if (expanded != stru->tokens->args[j])
// 		// 	free(stru->tokens->args[j]);
// 		stru->tokens->args[j] = expanded;
// 		j++;
// 	}
// }

void	main_expand(t_shell *str)
{
	char	*expanded;
	t_shell *stru;

	stru = str;
	while (stru->tokens)
	{
		expanded = expand_var(stru->tokens->str, stru);
		// if (expanded != stru->tokens->args[j])
		// 	free(stru->tokens->args[j]);
		stru->tokens->str = expanded;
		stru->tokens = stru->tokens->next;
	}
}
