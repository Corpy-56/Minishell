/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:56:23 by agouin            #+#    #+#             */
/*   Updated: 2025/10/09 14:21:07 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ignore_sigpipe_once(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = SIG_IGN;
	sigaction(SIGPIPE, &sa, NULL);
}

void	bad_fork(t_pipes *pipes)
{
	if (pipes->current->next)
	{
		close(pipes->fd[0]);
		close(pipes->fd[1]);
	}
	if (pipes->prev_read != -1)
		close(pipes->prev_read);
	_exit (1);
}

