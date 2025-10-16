/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_cmd2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:10:14 by sarah             #+#    #+#             */
/*   Updated: 2025/10/16 18:17:52 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	disable_echoctl1(void)
// {
// 	struct termios	term;
// 	t_term			termios;

// 	if (tcgetattr(STDIN_FILENO, &term) == -1)
// 		return ;
// 	termios.g_orig_termios1 = term;
// 	term.c_lflag &= ~(ECHOCTL);
// 	tcsetattr(STDIN_FILENO, TCSANOW, &term);
// }

// void	save_termios1(void)
// {
// 	t_term			termios;

// 	tcgetattr(STDIN_FILENO, &termios.g_saved_term1);
// }

// void	restore_termios1(void)
// {
// 	t_term			termios;

// 	tcsetattr(STDIN_FILENO, TCSANOW, &termios.g_saved_term1);
// }

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
	//apply_cmd_redirs_in_child(cmd, stru);
	if (cmd->fd_out_put1 != -2)
		close_fds(&cmd->fd_out_put1);
	if(cmd->fd_out_put2 != -2)
		close_fds(&cmd->fd_out_put2);
	if (cmd->fd_int_put != -2)
		close_fds(&cmd->fd_int_put);
	// apply_cmd_redirs_in_child(cmd);
	// close_fd(cmd); ajout amandine recent
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
	signal(SIGINT, SIG_IGN);// il est ultra important 
	// signal(SIGQUIT, SIG_IGN);
	// save_termios1();
	pid = fork();
	if (pid < 0)
		return (stru->last_status = 1);
	if (pid == 0)
		run_child(cmd, stru, f);
	status = collect_status(pid, stru);
	if (cmd->heredoc != NULL && f >= 0) //amandine
		close_fds(&f);
	ft_signal();
	return (status);
}
