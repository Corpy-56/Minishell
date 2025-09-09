/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 16:51:06 by agouin            #+#    #+#             */
/*   Updated: 2025/09/08 16:54:29 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_tokens(t_tokens *token)
{
	int	count;

	count = 0;
	while (token)
	{
		count++;
		token = token->next;
	}
	return (count);
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

void	ft_quote(char *rl, int i)
{
	int	quote1;

	quote1 = 0;
	while (rl[i])
	{
		if (quote1 == 0 && rl[i] == '\'')
		{
			i++;
			while (rl[i] != '\'' && rl[i])
				i++;
			if (rl[i] == '\0')
				quote1++;
		}
		else if (quote1 == 0 && rl[i] == '\"')
		{
			i++;
			while (rl[i] != '\"' && rl[i])
				i++;
			if (rl[i] == '\0')
				quote1++;
		}
		i++;
	}
	if (quote1 != 0)
		ft_error(1, "", NULL);// faire un autre message derreur ?? 
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

char	**args_from_tokens(t_tokens *token)
{
	int		i;
	int		count;
	char	**args;

	i = 0;
	count = count_tokens(token);
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	while (token)
	{
		args[i] = ft_strdup(token->str);
		i++;
		token = token->next;
	}
	args[i] = NULL;
	return (args);
}
