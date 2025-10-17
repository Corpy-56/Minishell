/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 14:32:46 by skuor             #+#    #+#             */
/*   Updated: 2025/10/17 17:00:39 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_heredoc(t_shell *stru)
{
	clean_cmd(stru);
	clean_env(stru);
}

t_cmd	*ft_dup_out(t_cmd *head)
{
	dup2(head->fd_out_put1, STDOUT_FILENO);
	close(head->fd_out_put1);
	return (head);
}

int	ft_first_ft_redirections(t_cmd *head, int fd, t_shell *stru)
{
	if (head->heredoc != NULL && (fd == -2 || fd == 0))
	{
		fd = ft_setup_heredoc(head, stru);
		if (fd == -1)
			return (fd);
		fd = ft_expand_heredoc(fd, stru, 0);
		if (fd == -1)
			return (-1);
	}
	if (head->fd_out_put1 >= 0 && head->here == -2)
		head = ft_dup_out(head);
	if (head->fd_out_put2 != -2 && head->here == -2)
	{
		dup2(head->fd_out_put2, STDOUT_FILENO);
		close(head->fd_out_put2);
	}
	if (head->fd_int_put >= 0)
	{
		dup2(head->fd_int_put, STDIN_FILENO);
		close(head->fd_int_put);
	}
	return (fd);
}


void	clean_after_parent(t_shell *stru)
{
	if (!stru)
		return ;
	if (stru->commande)
	{
		free_cmds(stru->commande);
		stru->commande = NULL;
	}
	if (stru->tokens)
	{
		free_tokens(stru->tokens);
		stru->tokens = NULL;
	}
	if (stru->path_dirs)
	{
		free_doublechar(stru->path_dirs);
		stru->path_dirs = NULL;
	}
}