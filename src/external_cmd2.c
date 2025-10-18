/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_cmd2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:10:14 by sarah             #+#    #+#             */
/*   Updated: 2025/10/17 19:17:09 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_child(t_cmd *cmd, t_shell *stru, int f)
{
	(void)f;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (cmd->heredoc != NULL && f >= 0)
	{
		dup2(f, STDIN_FILENO);
		close_fds(&f);
		f = -1;
	}
	else if (isatty(cmd->here) == 1 && cmd->here >= 0)
		close(cmd->here);
	if (cmd->fd_out_put1 != -2)
		close_fds(&cmd->fd_out_put1);
	if (cmd->fd_out_put2 != -2)
		close_fds(&cmd->fd_out_put2);
	if (cmd->fd_int_put != -2)
		close_fds(&cmd->fd_int_put);
	close_fd(cmd);
	exec_external(cmd, stru);
	clean_children(stru);
	_exit(stru->last_status);
}

int	run_external(t_cmd *cmd, t_shell *stru, int f)
{
	int		pid;
	int		status;

	(void)f;
	(void)stru;
	status = 0;
	if (cmd->args[0] == NULL)
		return (0);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		return (stru->last_status = 1);
	if (pid == 0)
		run_child(cmd, stru, f);
	status = collect_status(pid, stru);
	if (cmd->heredoc != NULL && f >= 0)
		close_fds(&f);
	ft_signal();
	return (status);
}
