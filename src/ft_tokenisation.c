/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenisation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 11:07:35 by agouin            #+#    #+#             */
/*   Updated: 2025/08/20 12:11:16 by skuor            ###   ########.fr       */
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
		ft_error(1, "", NULL);// faire un autre message derreur ?? 
}

t_tokens	*ft_creat_token(char *temp)
{
	t_tokens	*token;

	token = ft_calloc(sizeof(t_tokens), 1);
	if (!token)
		return (NULL);
	if (temp)
		token->str = ft_strdup(temp);
	else
		token->str = NULL;
	token->next = NULL;
	return (token);
}

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

/* t_tokens	*ft_tokenisation(char *rl, t_tokens *token)
{
	int			i;
	char		*temp;
	t_tokens	*a_debut;
	t_tokens	*fin;

	i = 0;
	fin = NULL;
	a_debut = NULL;
	token = NULL;
	temp = NULL;
	ft_quote(rl, i);
	while (rl[i])
	{
		while (rl[i] == 32 || rl[i] == 9)
			i++;
		if (!rl[i])
			break ;
		if (rl[i] == '\"' || rl[i] == '\'' || rl[i] == '<'
			|| rl[i] == '>' || rl[i] == '|')
		{
			temp = ft_tokenisation_quote(rl, temp, i);
			i = ft_strlen(temp) + i;
		}
		else
		{
			while (rl[i] && rl[i] != 32 && rl[i] != 9 && rl[i] != '<'
				&& rl[i] != '>' && rl[i] != '|' && rl[i] != '\''
				&& rl[i] != '\"')
				temp = ft_strjoin_char(temp, rl[i++]);
		}
		if (temp)
		{
			token = ft_creat_token(temp);
			free(temp);
			temp = NULL;
			if (!a_debut)
				a_debut = token;
			else
				fin->next = token;
			fin = token;
		}
	}
	return (a_debut);
} */

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
				token->str = ft_strjoin_char(token->str, rl[i]);
		}
		else if (rl[i] != 9 && rl[i] != 32 && rl[i])
			token->str = ft_strjoin_char(token->str, rl[i]);
		else if (rl[i] == 9 || rl[i] == 32 || rl[i] == '\0')
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
	//token = NULL;
	a_debut = NULL;
	fin = NULL;
	i = white_space(rl, i);
	ft_quote(rl, i);
	while (rl[i] && i != -1)
	{
		token = malloc(sizeof(t_tokens));
		if (!token)
			return (NULL);// faire une vrai sorti
		if (i == 0 || rl[i - 1] == 9 || rl[i - 1] == 32)
			token->str = NULL;
		if (rl[i] != 9 && rl[i] != 32 && rl[i])
			i = ft_one_token(rl, i, token);
		if (rl[i] == 9 || rl[i] == 32 || rl[i] == '\0')
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
		if (rl[i])
			i++;
	}
	//ft_type_token(a_debut);
	return (a_debut);
}

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

char **args_from_tokens(t_tokens *token)
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