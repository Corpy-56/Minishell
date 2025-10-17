/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:25:27 by skuor             #+#    #+#             */
/*   Updated: 2025/10/17 22:46:54 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_setup(t_pipes *pipes)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = pipes->current;
	if (pipes->prev_read != -1)
	{
		if (dup2(pipes->prev_read, STDIN_FILENO) == -1)
			_exit(1);
		close_fds(&pipes->prev_read);
	}
	if (cmd->next)
	{
		if (dup2(pipes->fd[1], STDOUT_FILENO) == -1)
			_exit(1);
		if (pipes->fd[0] != -1)
			close_fds(&pipes->fd[0]);
		if (pipes->fd[1] != -1)
			close_fds(&pipes->fd[1]);
	}
	if (cmd->here != -2 || cmd->fd_int_put != -2)
		i = ft_dup_stdin(cmd);
	if (i == -1)
		_exit(1);
}

int	ft_dup_stdin(t_cmd *cmd)
{
	if (cmd->here != -2)
	{
		if (dup2(cmd->here, STDIN_FILENO) == -1)
			return (-1);
	}
	if (cmd->fd_int_put != -2)
	{
		if (dup2(cmd->fd_int_put, STDIN_FILENO) == -1)
			return (-1);
	}
	return (0);
}

t_cmd	*child_exec_setup(t_pipes *pipes)
{
	t_cmd	*cmd;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	cmd = pipes->current;
	child_setup(pipes);
	return (cmd);
}
