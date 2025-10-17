/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:25:27 by skuor             #+#    #+#             */
/*   Updated: 2025/10/17 23:13:30 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	parent_after_fork(t_pipes *pipes)
{
	pipes->n++;
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

static void	wait_children(t_pipes *pipes, t_shell *sh)
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
		if (WIFSIGNALED(pipes->status) && WTERMSIG(pipes->status) == SIGINT)
			printf("\n");
		pipes->i++;
	}
	clean_after_parent(sh);
}

t_pipes	close_fd_child(t_pipes pipes)
{
	if (pipes.current->here >= 0)
		pipes.f.fd_here = pipes.current->here;
	if (pipes.current->fd_int_put >= 0)
		pipes.f.fd_int = pipes.current->fd_int_put;
	if (pipes.current->fd_out_put1 >= 0)
		pipes.f.fd_out1 = pipes.current->fd_out_put1;
	if (pipes.current->fd_out_put2 >= 0)
		pipes.f.fd_out2 = pipes.current->fd_out_put2;
	return (pipes);
}

t_pipes	ft_close_fd_test(t_pipes pipes)
{
	if (pipes.f.fd_here > 0 && pipes.current->here < 0)
		close(pipes.f.fd_here);
	if (pipes.current->fd_int_put >= 0 && pipes.f.fd_int < 0)
		close(pipes.f.fd_int);
	if (pipes.current->fd_out_put1 >= 0 && pipes.f.fd_out1 < 0)
		close(pipes.f.fd_out1);
	if (pipes.current->fd_out_put2 < 0 && pipes.f.fd_out2 >= 0)
		close(pipes.f.fd_out2);
	ft_fd_test();
	return (pipes);
}

void	run_pipes(t_cmd *head, t_shell *sh)
{
	t_pipes		pipes;

	init_pipes(&pipes, head);
	pipes.current = ft_test_heredoc_pipes(pipes.current, sh);
	if (pipes.current == NULL)
		return ;
	while (pipes.current)
	{
		if (pipes.current->next && pipe(pipes.fd) == -1)
		{
			if (pipes.prev_read != -1)
				close_fds (&pipes.prev_read);
			sh->last_status = 1;
			break ;
		}
		pipes = close_fd_child(pipes);
		pipes.pid = fork();
		bad_fork(&pipes, sh);
		if (pipes.pid == 0)
		{
			pipes = ft_close_fd_test(pipes);
			child_exec(&pipes, sh);
		}
		parent_after_fork(&pipes);
	}
	if (pipes.prev_read != -1)
		close_fds(&pipes.prev_read);
	wait_children(&pipes, sh);
	sh->last_status = pipes.last_status;
}
