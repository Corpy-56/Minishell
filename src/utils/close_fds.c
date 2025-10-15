/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 18:23:30 by skuor             #+#    #+#             */
/*   Updated: 2025/10/15 18:48:24 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds(int *fd)
{
	if (!fd)
		return ;
	if (*fd >= 0)
	{
		close(*fd);
		*fd = -1;
	}
}

// void	minishell_exit(t_shell *s, t_exec *e, int status)
// {

// 	end_of_line_restore(&e->fd_stdin, &e->fd_stdout);
// 	safe_close(&s->dup_0);
// 	safe_close(&s->dup_1);
// 	exit(status);
// }
