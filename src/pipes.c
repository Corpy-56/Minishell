/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:25:27 by skuor             #+#    #+#             */
/*   Updated: 2025/10/20 14:29:21 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	ft_signal();
	clean_after_parent(sh);
}

t_pipes	*close_fd_child(t_pipes *pipes)
{
	if (pipes->current->here >= 0)
		pipes->f.fd_here = pipes->current->here;
	if (pipes->current->fd_int_put >= 0)
		pipes->f.fd_int = pipes->current->fd_int_put;
	if (pipes->current->fd_out_put1 >= 0)
		pipes->f.fd_out1 = pipes->current->fd_out_put1;
	if (pipes->current->fd_out_put2 >= 0)
		pipes->f.fd_out2 = pipes->current->fd_out_put2;
	return (pipes);
}

t_pipes	*ft_close_fd_test(t_pipes *pipes)
{
	if (pipes->f.fd_here > 0 && pipes->current->here < 0)
		close(pipes->f.fd_here);
	if (pipes->current->fd_int_put < 0 && pipes->f.fd_int >= 0)
		close(pipes->f.fd_int);
	if (pipes->current->fd_out_put1 < 0 && pipes->f.fd_out1 >= 0)
		close(pipes->f.fd_out1);
	if (pipes->current->fd_out_put2 < 0 && pipes->f.fd_out2 >= 0)
		close(pipes->f.fd_out2);
	ft_fd_test();
	return (pipes);
}

static void	run_pipes2(t_pipes *pipes, t_shell *sh)
{
	while (pipes->current)
	{
		if (pipes->current->next && pipe(pipes->fd) == -1)
		{
			if (pipes->prev_read != -1)
				close_fds (&pipes->prev_read);
			sh->last_status = 1;
			break ;
		}
		pipes = close_fd_child(pipes);
		pipes->pid = fork();
		bad_fork(pipes, sh);
		if (pipes->pid == 0)
		{
			pipes = ft_close_fd_test(pipes);
			child_exec(pipes, sh);
			//close_fd(sh->commande);
		}
		signal(SIGINT, SIG_IGN);
		parent_after_fork(pipes, sh->commande);
	}
}

void	run_pipes(t_cmd *head, t_shell *sh)
{
	t_pipes	pipes;

	init_pipes(&pipes, head);
	pipes.current = ft_test_heredoc_pipes(pipes.current, sh);
	if (pipes.current == NULL)
		return ;
	run_pipes2(&pipes, sh);
	if (pipes.prev_read != -1)
		close_fds(&pipes.prev_read);
	wait_children(&pipes, sh);
	sh->last_status = pipes.last_status;
}
