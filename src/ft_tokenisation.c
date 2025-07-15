/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenisation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 11:07:35 by agouin            #+#    #+#             */
/*   Updated: 2025/07/15 15:29:40 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_char(char *str, const char c)
{
	int		i;
	char	*joined;

	if (str == NULL)
	{
		joined = malloc(2);
		if (joined == NULL)
			return (NULL);
		joined[0] = c;
		joined[1] = '\0';
		return (joined);
	}
	joined = malloc(ft_strlen(str) + 2);
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
		ft_error(1, "");
}

int	ft_one_token(char *rl, int i, t_tokens *token)
{
	while (rl[i])
	{
		if (rl[i] == '\'')
		{
			i++;
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

int	ft_test_commande(char *str)
{
	if (ft_strncmp(str, "ls", 2) == 0 || ft_strncmp(str, "cat", 3) == 0
		|| ft_strncmp(str, "grep", 4) == 0 || ft_strncmp(str, "wc", 2) == 0 
		|| ft_strncmp(str, "head", 4) == 0 || ft_strncmp(str, "tail", 4) == 0 
		|| ft_strncmp(str, "date", 4) == 0 || ft_strncmp(str, "sleep", 5) == 0
		|| ft_strncmp(str, "echo", 4) == 0 || ft_strncmp(str, "cd", 2) == 0
		|| ft_strncmp(str, "pwd", 3) == 0 || ft_strncmp(str, "export", 6) == 0
		|| ft_strncmp(str, "unset", 5) == 0 || ft_strncmp(str, "env", 3) == 0
		|| ft_strncmp(str, "exit", 4))
			return (0);
	return (1);
}

void	ft_type_token(t_tokens *a_debut)// verifier que ca marche bien 
{
	t_tokens	*p_actuel;
	int i;

	i = 0;
	p_actuel = a_debut;
	while (p_actuel)
	{
		if (ft_strncmp(p_actuel->str, "|", 1) == 0)
			p_actuel->type_i = 5;
		else if (ft_strncmp(p_actuel->str, "<<", 2) == 0)
			p_actuel->type_i = 4;
		else if (ft_strncmp(p_actuel->str, "<", 1) == 0)
			p_actuel->type_i = 3;
		else if (ft_strncmp(p_actuel->str, ">>", 2) == 0)
			p_actuel->type_i = 2;
		else if (ft_strncmp(p_actuel->str, ">", 1) == 0)
			p_actuel->type_i = 1;
		else if (ft_test_commande(p_actuel->str) == 0)
			p_actuel->type_i = 6;
		else if (p_actuel->str[0] == '-' && p_actuel->str[1] != '-' && p_actuel->str[1] != '\0')
			p_actuel->type_i = 7;
		else
			p_actuel->type_i = 0;
		p_actuel = p_actuel->next;
	}	
}// apres une redirection cest le nom dun fichier pour > et >>

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
	while (rl[i] && i != -1)
	{
		token = malloc(sizeof(t_tokens));
		if (token == NULL)
			return (NULL);// faire une vrai sorti
		if (i == 0 || rl[i - 1] == 9 || rl[i - 1] == 32)
			token->str = NULL;
		if (rl[i] != 9 && rl[i] != 32 && rl[i])
			i = ft_one_token(rl, i, token);
		if (rl[i] == 9 || rl[i] == 32 || rl[i + 1] == '\0')
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
	ft_type_token(a_debut);
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

