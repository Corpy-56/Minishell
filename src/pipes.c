/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:25:27 by skuor             #+#    #+#             */
/*   Updated: 2025/10/10 17:15:40 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_setup(t_pipes *pipes)
{
	t_cmd	*cmd;

	cmd = pipes->current;
	if (cmd->here != -2)
	{
		if (dup2(cmd->here, STDIN_FILENO) == -1)
			exit(1);
		if (cmd->fd_int_put != -2)
			close(cmd->here);
	}
	if (pipes->prev_read != -1)
	{
		if (dup2(pipes->prev_read, STDIN_FILENO) == -1)
			_exit(1);
		close(pipes->prev_read);
	}
	if (cmd->next)
	{
		if (dup2(pipes->fd[1], STDOUT_FILENO) == -1)
			_exit(1);
		close(pipes->fd[0]);
		close(pipes->fd[1]);
	}
}

void	child_exec(t_pipes *pipes, t_shell *stru)
{
	t_cmd	*cmd;

	cmd = pipes->current;
	child_setup(pipes);
	cmd->here = ft_first_ft_redirections(cmd, cmd->here, stru);
	if (cmd->here == -1)
	{
		ignore_sigpipe_once();
		clean_children(stru);
		_exit(1);
	}
	if (is_builtin(cmd))
	{
		ignore_sigpipe_once();
		pipes->builtins = ft_exec_builtins(cmd, stru, false);
		clean_children(stru);
		_exit(pipes->builtins);
	}
	else
	{
		ignore_sigpipe_once();
		exec_external(cmd, stru);
		clean_children(stru);
		_exit(127);
	}
}

void	parent_after_fork(t_pipes *pipes)
{
	pipes->n++;
	if (pipes->prev_read != -1)
		close(pipes->prev_read);
	if (pipes->current->next)
	{
		close(pipes->fd[1]);
		pipes->prev_read = pipes->fd[0];
	}
	else
		pipes->prev_read = -1;
	pipes->last_pid = pipes->pid;
	pipes->current = pipes->current->next;
}

void	wait_children(t_pipes *pipes)
{
	pipes->i = 0;
	pipes->status = 0;
	pipes->last_status = 0;
	while (pipes->i < pipes->n)
	{
		pipes->wait_child = wait(&pipes->status);
		if (pipes->wait_child == -1)
		{
			if (errno == EINTR)
				continue ;
			break ;
		}
		if (pipes->wait_child == pipes->last_pid)
			pipes->last_status = extract_exit_status(pipes->status);
		pipes->i++;
	}
}

void	run_pipes(t_cmd *head, t_shell *sh)
{
	t_pipes	pipes;

	init_pipes(&pipes, head);
	pipes.current = ft_test_heredoc_pipes(pipes.current, sh);
	while (pipes.current)
	{
		if (pipes.current->next && pipe(pipes.fd) == -1)
		{
			if (pipes.prev_read != -1)
				close (pipes.prev_read);
			sh->last_status = 1;
			// clean_children(sh);
			break ;
		}
		pipes.pid = fork();
		// if (pipes.pid == -1)
		bad_fork(&pipes, sh);
		if (pipes.pid == 0)
			child_exec(&pipes, sh);
		parent_after_fork(&pipes);
	}
	if (pipes.prev_read != -1)
		close(pipes.prev_read);
	wait_children(&pipes);
	sh->last_status = pipes.last_status;
}
