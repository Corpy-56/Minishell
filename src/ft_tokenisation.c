/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenisation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 11:07:35 by agouin            #+#    #+#             */
/*   Updated: 2025/10/18 10:22:51 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_one_token_extra(char *rl, int i, t_tokens *token)
{
	if (rl[i] == '$')
		token->dollars += 1;
	token->str = ft_strjoin_char(token->str, rl[i]);
	return (token->str);
}

int	ft_one_token2(char *rl, int i, t_tokens *token)
{
	if (rl[i] == '\'')
	{
		token->str = ft_strjoin_char(token->str, rl[i]);
		while (rl[++i] != '\0' && rl[i] != '\'')
			token->str = ft_strjoin_char(token->str, rl[i]);
		if (rl[i] == '\'')
			token->str = ft_strjoin_char(token->str, rl[i]);
		return (i);
	}
	else if (rl[i] == '\"')
	{
		token->str = ft_strjoin_char(token->str, rl[i]);
		while (rl[++i] != '\0' && rl[i] != '\"')
		{
			if (rl[i] == '$')
				token->dollars += 1;
			token->str = ft_strjoin_char(token->str, rl[i]);
		}
		if (rl[i] == '\"')
			token->str = ft_strjoin_char(token->str, rl[i]);
		return (i);
	}
	return (0);
}

int	ft_token_redirection(char *rl, int i, t_tokens *token)
{
	if (rl[i] == '<' || rl[i] == '>')
	{
		if (token->str == NULL)
		{
			while ((rl[i] == '<' || rl[i] == '>') && rl[i])
			{
				token->str = ft_strjoin_char(token->str, rl[i]);
				i++;
			}
		}
		return (i -1);
	}
	else if (rl[i] == '|')
	{
		if (token->str == NULL)
		{
			while (rl[i] == '|' && rl[i])
			{
				token->str = ft_strjoin_char(token->str, rl[i]);
				i++;
			}
		}
		return (i - 1);
	}
	return (0);
}

int	ft_one_token(char *rl, int i, t_tokens *token)
{
	while (rl[i])
	{
		if (rl[i] == '\'' || rl[i] == '\"')
			i = ft_one_token2(rl, i, token);
		else if (rl[i] == '<' || rl[i] == '>' || rl[i] == '|')
		{
			i = ft_token_redirection(rl, i, token);
			return (i);
		}
		else if (rl[i] != 9 && rl[i] != 32 && rl[i])
			token->str = ft_one_token_extra(rl, i, token);
		else if ((rl[i] != '<' || rl[i] != '>') && token->str == NULL)
			token->str = ft_strjoin_char(token->str, rl[i]);
		else if (rl[i] == 9 || rl[i] == 32 || rl[i] == '\0')
			return (i);
		i++;
	}
	return (i);
}

t_tokens	*ft_tokenisation(char *rl, t_tokens *token, int i)
{
	t_tokens	*a_debut;
	t_tokens	*fin;

	a_debut = NULL;
	fin = NULL;
	i = ft_init_tokenisation(rl, i);
	while (i != -1 && rl[i])
	{
		token = ft_creat_token(rl, i);
		if (rl[i] && rl[i] != 9 && rl[i] != 32)
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
	ft_test_minishell(a_debut);
	return (a_debut);
}