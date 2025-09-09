/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenisation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 11:07:35 by agouin            #+#    #+#             */
/*   Updated: 2025/09/09 14:15:14 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_tokenisation_quote(char *rl, char *temp, int i)
{
	char	quote;

	if (rl[i] == '\"' || rl[i] == '\'')
	{
		quote = rl[i++];
		temp = ft_strjoin_char(temp, quote);
		while (rl[i] && rl[i] != quote)
			temp = ft_strjoin_char(temp, rl[i++]);
		if (rl[i++] == quote)
			temp = ft_strjoin_char(temp, quote);
	}
	else if ((rl[i] == '<' || rl[i] == '>'))
	{
		while ((rl[i] == '<' || rl[i] == '>') && rl[i])
			temp = ft_strjoin_char(temp, rl[i++]);
	}
	else if (rl[i] == '|')
	{
		while (rl[i] == '|' && rl[i])
			temp = ft_strjoin_char(temp, rl[i++]);
	}
	return (temp);
}

char	*ft_one_token_extra(char *rl, int i, t_tokens *token)
{
	if (rl[i] == '$')
		token->dollars += 1;
	token->str = ft_strjoin_char(token->str, rl[i]);
	return (token->str);
}

int	ft_one_token(char *rl, int i, t_tokens *token)
{
	while (rl[i])
	{
		if (rl[i] == '\'')
		{
			while (rl[++i] != '\0' && rl[i] != '\'')
				token->str = ft_strjoin_char(token->str, rl[i]);
		}
		else if (rl[i] == '\"')
		{
			while (rl[++i] != '\0' && rl[i] != '\"')
			{
				if (rl[i] == '$')
					token->dollars += 1;
				token->str = ft_strjoin_char(token->str, rl[i]);
			}
		}
		else if (rl[i] != 9 && rl[i] != 32 && rl[i])
			token->str = ft_one_token_extra(rl, i, token);
		else if (rl[i] == 9 || rl[i] == 32 || rl[i] == '\0')
			return (i);
		i++;
	}
	return (i);
}

t_tokens	*ft_creat_token(char *rl, int i)
{
	t_tokens	*token;

	token = ft_calloc(sizeof(t_tokens), 1);
	if (token == NULL)
		return (NULL);
	if (i == 0 || rl[i - 1] == 9 || rl[i - 1] == 32)
		token->str = NULL;
	token->dollars = 0;
	return (token);
}

t_tokens	*ft_tokenisation(char *rl, t_tokens *token)
{
	int	i;

	auto t_tokens * a_debut = NULL, *fin = NULL;
	i = 0;
	token = NULL;
	i = white_space(rl, i);
	ft_quote(rl, i);
	while (rl[i] && i != -1)
	{
		token = ft_creat_token(rl, i);
		if (rl[i] != 9 && rl[i] != 32 && rl[i])
			i = ft_one_token(rl, i, token);
		token->next = NULL;
		if (token == NULL)
			return (NULL);
		if (a_debut == NULL)
			a_debut = token;
		else
			fin->next = token;
		fin = token;
		if (rl[i])
			i++;
	}
	return (a_debut);
}

