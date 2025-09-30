/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:59:00 by skuor             #+#    #+#             */
/*   Updated: 2025/09/30 15:26:32 by skuor            ###   ########.fr       */
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
		if (current->cmd == NULL)
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
