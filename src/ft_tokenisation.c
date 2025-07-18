/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenisation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 11:07:35 by agouin            #+#    #+#             */
/*   Updated: 2025/07/18 16:24:29 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		ft_error(1, "");// faire un autre message derreur ?? 
}

int	ft_one_token(char *rl, int i, t_tokens *token)
{
	while (rl[i])
	{
		if (rl[i] == '\'')
		{
			while (rl[i] != '\0' && rl[i] != 32 && rl[i] != 9)
				token->str = ft_strjoin_char(token->str, rl[i++]);
		}
		else if (rl[i] == '\"')
		{
			while (rl[i] != '\0' && rl[i] != 32 && rl[i] != 9)
				token->str = ft_strjoin_char(token->str, rl[i++]);
		}
		else if (rl[i] != 9 && rl[i] != 32 && rl[i])
			token->str = ft_strjoin_char(token->str, rl[i]);
		if (rl[i] == 9 || rl[i] == 32 || rl[i] == '\0')
			return (i);
		i++;
	}
	return (i);
}

t_tokens	*ft_tokenisation(char *rl, t_tokens *token)
{
	t_tokens	*a_debut;
	t_tokens	*fin;
	int	i;

	i = 0;
	token = NULL;
	a_debut = NULL;
	fin = NULL;
	ft_quote(rl, i);
	i = white_space(rl, i);
	while(rl[i] && i != -1)
	{
		token = ft_calloc(sizeof(t_tokens), 1);
		if (token == NULL)
			return (NULL);// faire une vrai sorti
		if (i == 0 || rl[i - 1] == 9 || rl[i - 1] == 32)
			token->str = NULL;
		if (rl[i] != 9 && rl[i] != 32 && rl[i])
			i = ft_one_token(rl, i, token);
		if (rl[i] == 9 || rl[i] == 32 || rl[i + 1] == '\0' || rl[i] == '\0')
		{
			if (token->str != NULL)
			{
				token->next = NULL;	
				if (a_debut == NULL)
				{
					a_debut = token;
					fin = token;
				}
				else
				{
					fin->next = token;
					fin = token;
				}
			}
		}
		i++;
	}
	return (a_debut);
}


//t_tokens	*ft_new_node_token(t_tokens *token, t_tokens *a_debut, t_tokens *fin)
//{
//	a_debut = NULL;
//	fin = NULL;
//	if (token->str != NULL)
//	{
//		token->next = NULL;	
//		if (a_debut == NULL)
//		{
//			a_debut = token;
//			fin = token;
//		}
//		else
//		{
//			fin->next = token;
//			fin = token;
//		}
//	}
//	return (a_debut);	
//}

//t_tokens	*ft_tokenisation(char *rl, t_tokens *token)
//{
//	int	i;
//	t_tokens	*a_debut;
//	t_tokens	*fin;

//	i = 0;
//	token = NULL;
//		a_debut = NULL;
//	fin = NULL;
//	ft_quote(rl, i);
//	i = white_space(rl, i);
//	while(rl[i] && i != -1)
//	{
//		token = malloc(sizeof(t_tokens));
//		if (token == NULL)
//			return (NULL); // faire une vrai sorti
//		if (i == 0 || rl[i - 1] == 9 || rl[i - 1] == 32)
//			token->str = NULL;
//		if (rl[i] != 9 && rl[i] != 32 && rl[i])
//		{
//			i = ft_one_token(rl, i, token);
//			if (token->str == NULL)
//				return (NULL); // pareil
//		}
//		if (rl[i] == 9 || rl[i] == 32 || rl[i + 1] == '\0')
//			token = ft_new_node_token(token, a_debut, fin);
//		i++;
//	}
//	return (token);
//}