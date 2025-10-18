/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:16:15 by skuor             #+#    #+#             */
/*   Updated: 2025/10/18 10:22:18 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_exit_status(t_shell *stru, char **str)
{
	char	*status_str;

	status_str = ft_itoa(stru->last_status);
	append_str(str, status_str);
	free(status_str);
}

static char	*free_and_null(char *out)
{
	free(out);
	return (NULL);
}

static int	append_part(char **dst, char *src, size_t j, size_t i)
{
	while (j < i)
	{
		if (append_char(dst, src[j]) < 0)
			return (-1);
		j++;
	}
	return (0);
}

static int	handle_dollar(t_expand *exp, t_shell *stru, size_t *i)
{
	if (append_part(&exp->out, exp->str, exp->start, *i) < 0)
		return (-1);
	if (*i + 1 < exp->len_str && exp->str[*i + 1] == '?')
	{
		expand_exit_status(stru, &exp->out);
		*i += 2;
	}
	else
		*i = expand_var2(stru, exp->str, *i + 1, &exp->out);
	exp->start = *i;
	return (0);
}

char	*expand_var(t_tokens *token, t_shell *stru, size_t i)
{
	t_expand	exp;

	init_expand(&exp, token, i);
	if (!exp.out)
		return (NULL);
	while (i < exp.len_str)
	{
		if (exp.str[i] == '$' && token->dollars >= 1)
		{
			if (handle_dollar(&exp, stru, &i) < 0)
				return (free_and_null(exp.out));
		}
		else
			i++;
	}
	if (append_part(&exp.out, exp.str, exp.start, i) < 0)
		return (free_and_null(exp.out));
	return (exp.out);
}

// char	*expand_var(t_tokens *token, t_shell *stru, size_t i)
// {
// 	char	*str;
// 	size_t	len_str;
// 	size_t	start;
// 	size_t	j;

// 	str = ft_calloc(1, 1);
// 	if (!str)
// 		return (NULL);
// 	len_str = ft_strlen(token->str);
// 	start = i;
// 	while (i < len_str)
// 	{
// 		if (token->str[i] == '$' && token->dollars >= 1)
// 		{
// 			j = start;
// 			while (j < i)
// 			{
// 				if (append_char(&str, token->str[j]) < 0)
// 				{
// 					free(str);
// 					return (NULL);
// 				}
// 				j++;
// 			}
// 			if (i + 1 < len_str && token->str[i + 1] == '?')
// 			{
// 				expand_exit_status(stru, &str);
// 				i += 2;
// 			}
// 			else
// 				i = expand_var2(stru, token->str, i + 1, &str);
// 			start = i;
// 		}
// 		else
// 			i++;
// 	}
// 	j = start;
// 	while (j < i)
// 	{
// 		if (append_char(&str, token->str[j]) < 0)
// 		{
// 			free(str);
// 			return (NULL);
// 		}
// 		j++;
// 	}
// 	return (str);
// }