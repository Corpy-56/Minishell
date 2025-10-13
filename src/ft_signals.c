/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:39:18 by agouin            #+#    #+#             */
/*   Updated: 2025/10/13 15:06:12 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell *g_shell = NULL;

void	set_shell(t_shell *shell)
{
	g_shell = shell;
}

void	signal_handler1(int signum)
{
	(void)signum;
	if (g_shell)
		g_shell->last_status = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);//efface la ligne
	rl_on_new_line();//remet une ligne 
	rl_redisplay();// reaffiche le prompt propremment             SIGQUIT pour controle (\)
}

void	ft_signal(void)
{
	signal(SIGINT, signal_handler1);
	signal(SIGQUIT, SIG_IGN);
}

