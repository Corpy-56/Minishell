/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_token_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:42:37 by agouin            #+#    #+#             */
/*   Updated: 2025/10/18 13:00:39 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	error_chevrons(t_tokens *p_actuel)
{
	if (ft_strncmp(p_actuel->str, ">>>>", 4) == 0)
		return (err_msg_syntax(">>"), 2);
	else if (ft_strncmp(p_actuel->str, ">>>", 3) == 0)
		return (err_msg_syntax(">"), 2);
	else if (ft_strncmp(p_actuel->str, "<<<<", 4) == 0)
		return (err_msg_syntax("<<"), 2);
	else if (ft_strncmp(p_actuel->str, "<<<", 3) == 0)
		return (err_msg_syntax("newline"), 2);
	else if (ft_strncmp(p_actuel->str, "><", 2) == 0)
		return (err_msg_syntax("<"), 2);
	else if (ft_strncmp(p_actuel->str, ">", 1) == 0
		|| ft_strncmp(p_actuel->str, "<", 1) == 0)
	{
		if (p_actuel->next == NULL)
			return (err_msg_syntax("newline"), 2);
		if (p_actuel->next->str == NULL)
			return (err_msg_syntax("newline"), 2);
		else if (ft_strncmp(p_actuel->next->str, ">", 1) == 0
			|| ft_strncmp(p_actuel->next->str, "<", 1) == 0)
			return (err_msg_syntax(p_actuel->next->str), 2);
	}
	return (0);
}

int	ft_valid_syntax(t_tokens *token)
{
	t_tokens	*p_actuel;

	p_actuel = token;
	if (p_actuel && ft_strncmp(p_actuel->str, "||", 2) == 0)
		return (err_msg_syntax("||"), 2);
	if (p_actuel && ft_strncmp(p_actuel->str, "|", 1) == 0)
		return (err_msg_syntax("|"), 2);
	while (p_actuel != NULL)
	{
		if ((p_actuel->next == NULL && ft_strncmp(p_actuel->str, "|", 1) == 0))
			return (err_msg_syntax("|"), 2);
		else if (ft_strncmp(p_actuel->str, "||", 2) == 0)
			return (err_msg_syntax("||"), 2);
		if (error_chevrons(p_actuel))
			return (2);
		p_actuel = p_actuel->next;
	}
	return (0);
}

int	ft_nb_tokens(t_tokens *p_actuel)
{
	int			i;
	t_tokens	*a_debut;

	i = 1;
	a_debut = p_actuel;
	while (a_debut && a_debut->str[0] != '|')
	{
		i++;
		a_debut = a_debut->next;
	}
	return (i);
}

t_cmd	*ft_extra_lexer(t_tokens *p_actuel, t_cmd *commande, int j, int i)
{
	commande->cmd = ft_strdup(p_actuel->str);
	if (!commande->cmd)
	{
		free_one_cmd(commande);
		return (NULL);
	}
	commande->args = ft_calloc(sizeof(char *), i);
	commande->args[0] = ft_strdup(p_actuel->str);
	if (!commande->args[0])
	{
		free_one_cmd(commande);
		return (NULL);
	}
	j = 1;
	commande->args[j] = NULL;
	return (commande);
}

t_cmd	*lexer_cmd(t_cmd *commande, t_tokens *p_actuel, int i, int j)
{
	i = ft_nb_tokens(p_actuel);
	if (commande->cmd == NULL && is_assignment_word(p_actuel->str))
		return (commande);
	if (commande->cmd == NULL)
		commande = ft_extra_lexer(p_actuel, commande, j, i);
	else if (commande->cmd != NULL)
	{
		while (commande->args[j] != NULL)
			j++;
		commande->args[j] = ft_strdup(p_actuel->str);
		if (!commande->args[j])
		{
			free_one_cmd(commande);
			return (NULL);
		}
		j++;
		commande->args[j] = NULL;
	}
	return (commande);
}
