/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:59:00 by skuor             #+#    #+#             */
/*   Updated: 2025/10/16 18:55:13 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_one_maillon(t_cmd *cmd)
{
	if (!cmd)
		return ;
	free_doublechar(cmd->args);
	free(cmd->cmd);
	free(cmd);
}

t_cmd	*suppr_empty_cmd(t_cmd *head)
{
	t_cmd	*prev;
	t_cmd	*current;
	t_cmd	*next;

	prev = NULL;
	current = head;
	while (current)
	{
		if (current == NULL)
		{
			next = current->next;
			if (prev)
				prev->next = next;
			else
				head = next;
			current->next = NULL;
			free_one_maillon(current);
			current = next;
			continue ;
		}
		prev = current;
		current = current->next;
	}
	return (head);
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

t_cmd	*ft_test_no_errors(t_cmd *commande)
{
	t_cmd	*a;

	a = commande;
	while (a)
	{
		if (a->fd_int_put == -1 || a->fd_out_put1 == -1 || a->fd_out_put2 == -1)
			return (NULL);
		a = a->next;
	}
	return (commande);
}
