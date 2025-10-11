/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenisation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 11:07:35 by agouin            #+#    #+#             */
/*   Updated: 2025/10/11 18:46:41 by skuor            ###   ########.fr       */
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


void	ft_ignore_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_test_minishell(t_tokens *a_debut)
{
	int			i;
	t_tokens	*p_actuel;

	i = 0;
	p_actuel = a_debut;
	while (p_actuel != NULL)
	{
		if (p_actuel->str != NULL)
		{
			if(ft_strncmp(p_actuel->str, "./minishell", ft_strlen(p_actuel->str)) == 0)
			{
				ft_ignore_signal();
				i++;
				if (i >= 2)
					printf("minishell: recursive execution blocked\n");
			}
		}
		p_actuel = p_actuel->next;
	}
}

t_tokens	*ft_tokenisation(char *rl, t_tokens *token, int i)
{
	t_tokens	*a_debut;
	t_tokens	*fin;
	int k;

	k = 0;
	a_debut = NULL;
	fin = NULL;
	i = white_space(rl, i);
	if (i <= 0)
		k = ft_quote(rl, i);
	if (k == -1)
		return (NULL);
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


// t_tokens	*ft_tokenisation(char *rl, t_tokens *token, t_shell *stru)
// {
// 	int	i;
// 	(void)stru;

// 	auto t_tokens * a_debut = NULL, *fin = NULL;
// 	i = 0;
// 	token = NULL;
// 	i = white_space(rl, i);
// 	if (i <= 0)
// 		ft_quote(rl);
// 	while (i != -1 && rl[i])
// 	{
// 		i = white_space(rl, i);
// 		if (!rl[i])
// 			break ;
// 		token = ft_creat_token(rl, i);
// 		// if (rl[i] && rl[i] != 9 && rl[i] != 32)
// 			// i = ft_one_token(rl, i, token);
// 		if (token == NULL)
// 			return (NULL);
// 		token->next = NULL;
// 		i = ft_one_token(rl, i, token);
// 		if (a_debut == NULL)
// 			a_debut = token;
// 		else
// 			fin->next = token;
// 		fin = token;
// 		if (rl[i])
// 			i++;
// 		i = white_space(rl, i);
// 	}
// 	// ft_test_minishell(a_debut, stru);
// 	return (a_debut);
// }

