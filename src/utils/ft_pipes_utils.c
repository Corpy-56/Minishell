/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:25:27 by skuor             #+#    #+#             */
/*   Updated: 2025/10/20 14:27:54 by agouin           ###   ########.fr       */
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

void	child_exec(t_pipes *pipes, t_shell *stru)
{
	t_cmd	*cmd;

	cmd = child_exec_setup(pipes);
	cmd->here = ft_first_ft_redirections(cmd, cmd->here, stru);
	if (cmd->here == -1)
	{
		apply_cmd_redirs_in_child(cmd, stru);
		clean_children(stru);
		_exit(1);
	}
	if (is_builtin(cmd))
	{
		pipes->builtins = ft_exec_builtins(cmd, stru, false);
		apply_cmd_redirs_in_child(cmd, stru);
		clean_children(stru);
		_exit(pipes->builtins);
	}
	else
	{
		exec_external(cmd, stru);
		apply_cmd_redirs_in_child(cmd, stru);
		clean_children(stru);
		_exit(127);
	}
	apply_cmd_redirs_in_child(cmd, stru);
}

void	parent_after_fork(t_pipes *pipes, t_cmd *cmd)
{
	pipes->n++;
	close_fd(cmd);
	if (pipes->prev_read != -1)
		close_fds(&pipes->prev_read);
	if (pipes->current->next)
	{
		close_fds(&pipes->fd[1]);
		pipes->prev_read = pipes->fd[0];
	}
	else
		pipes->prev_read = -1;
	if (isatty(pipes->current->here) == 1 && pipes->current->here >= 0)
		close(pipes->current->here);
	pipes->last_pid = pipes->pid;
	pipes->current = pipes->current->next;
}
