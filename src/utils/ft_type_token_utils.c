/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_token_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:42:37 by agouin            #+#    #+#             */
/*   Updated: 2025/09/30 15:26:08 by skuor            ###   ########.fr       */
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
		if (p_actuel->next == NULL
			|| ft_is_str_isprint(p_actuel->next->str) == 0)
			return (err_msg_syntax("newline"), 2);
		else if (ft_strncmp(p_actuel->next->str, ">", 1) == 0)
			return (err_msg_syntax(">"), 2);
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

void	ft_initialization_commande(t_cmd *commande)
{
	commande->args = NULL;
	commande->cmd = NULL;
	commande->heredoc = NULL;
	commande->fd_int_put = -2;
	commande->next = NULL;
	commande->fd_out_put1 = -2;
	commande->fd_out_put2 = -2;
	commande->next = NULL;
	return ;
}

t_cmd	*ft_creat_token2(void)
{
	t_cmd	*commande;

	commande = ft_calloc(sizeof(t_cmd), 1);
	if (!commande)
		return (NULL);
	ft_initialization_commande(commande);
	return (commande);
}

t_cmd	*lexer_cmd(t_cmd *commande, t_tokens *p_actuel)
{
	int	i;
	int	j;

	if (commande->cmd == NULL && is_assignment_word(p_actuel->str))
		return (commande);
	i = ft_nb_tokens(p_actuel);
	j = 0;
	if (commande->cmd == NULL)
	{
		commande->cmd = ft_strdup(p_actuel->str);
		commande->args = ft_calloc(sizeof(char *), i);
		commande->args[0] = ft_strdup(p_actuel->str);
		j = 1;
		commande->args[j] = NULL;
	}
	else if (commande->cmd != NULL)
	{
		while (commande->args[j] != NULL)
			j++;
		commande->args[j] = ft_strdup(p_actuel->str);
		j++;
		commande->args[j] = NULL;
	}
	return (commande);
}
