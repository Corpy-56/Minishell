/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:39:18 by agouin            #+#    #+#             */
/*   Updated: 2025/10/11 18:01:37 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	signal_handler1(int signum)
{
	(void)signum;
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

