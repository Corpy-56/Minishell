/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_cmd2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:10:14 by sarah             #+#    #+#             */
/*   Updated: 2025/10/15 14:14:56 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static struct termios	g_orig_termios1;
struct termios			g_saved_term1;

void	disable_echoctl1(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return ;
	g_orig_termios1 = term;
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	save_termios1(void)
{
	tcgetattr(STDIN_FILENO, &g_saved_term1);
}

void	restore_termios1(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &g_saved_term1);
}


static void	run_child(t_cmd *cmd, t_shell *stru, int f)
{
	(void)f;
	disable_echoctl1();
	signal(SIGQUIT, SIG_IGN);
	if (cmd->heredoc != NULL && f >= 0)
	{
		dup2(f, STDIN_FILENO);
		close(f);
		f = -1;
	}
	apply_cmd_redirs_in_child(cmd);
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
	save_termios1();
	pid = fork();
	if (pid < 0)
		return (stru->last_status = 1);
	if (pid == 0)
		run_child(cmd, stru, f);
	status = collect_status(pid, stru);
	restore_termios1();
	ft_signal();
	return (status);
}
