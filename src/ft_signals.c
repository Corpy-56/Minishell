/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:39:18 by agouin            #+#    #+#             */
/*   Updated: 2025/10/19 17:31:15 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*g_shell = NULL;

void	set_shell(t_shell *shell)
{
	g_shell = shell;
}

void	signal_handler1(int signum)
{
	t_shell	*shell;

	shell = NULL;
	(void)signum;
	if (g_shell)
		g_shell->last_status = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	shell = static_struct(shell);
}

void	ft_signal(void)
{
	signal(SIGINT, signal_handler1);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_ignore_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
