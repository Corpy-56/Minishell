/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:33:30 by skuor             #+#    #+#             */
/*   Updated: 2025/10/17 16:58:37 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_maillons(t_cmd *cmd)
{
	int	n;

	n = 0;
	while (cmd)
	{
		n++;
		cmd = cmd->next;
	}
	return (n);
}

t_cmd	*ft_test_heredoc_pipes(t_cmd *cmds, t_shell *sh)
{
	t_cmd	*p_actuel;

	p_actuel = cmds;
	while (p_actuel)
	{
		if (p_actuel->heredoc != NULL)
		{
			p_actuel->here = ft_setup_heredoc(p_actuel, sh);
			if (p_actuel->here == -1)
				return (NULL);
			p_actuel->here = ft_expand_heredoc(p_actuel->here, sh, 0);
		}
		p_actuel = p_actuel->next;
	}
	return (cmds);
}

void	ft_first_ft_redirections2(t_cmd *head)
{
	if (head->fd_out_put1 != -2)
	{
		dup2(head->fd_out_put1, STDOUT_FILENO);
		close_fds(&head->fd_out_put1);
	}
	if (head->fd_out_put2 != -2)
	{
		dup2(head->fd_out_put2, STDOUT_FILENO);
		close_fds(&head->fd_out_put2);
	}
	if (head->fd_int_put != -2)
	{
		dup2(head->fd_int_put, STDIN_FILENO);
		close_fds(&head->fd_int_put);
	}
}
