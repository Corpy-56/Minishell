/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:56:23 by agouin            #+#    #+#             */
/*   Updated: 2025/10/15 18:45:41 by skuor            ###   ########.fr       */
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

void	bad_fork(t_pipes *pipes, t_shell *sh)
{
	if (pipes->pid == -1)
	{
		if (pipes->current->next)
		{
			close_fds(&pipes->fd[0]);
			close_fds(&pipes->fd[1]);
		}
		if (pipes->prev_read != -1)
			close_fds(&pipes->prev_read);
		sh->last_status = 1;
		return ;
	}
}

char	*join_three_char(char *a, char *b, char *c)
{
	char	*ab;
	char	*abc;

	ab = ft_strjoin(a, b);
	if (ab)
		abc = ft_strjoin(ab, c);
	else
		abc = NULL;
	free(ab);
	return (abc);
}

t_shell	*static_struct(t_shell *stru)
{
	static t_shell	*tmp = NULL;

	if (stru)
		tmp = stru;
	return (tmp);
}

bool	is_exec_file(const char *chosen_path)
{
	struct stat	info;

	if (!chosen_path)
		return (false);
	if (stat(chosen_path, &info) != 0)
		return (false);
	if (S_ISDIR(info.st_mode))
		return (false);
	if (access(chosen_path, X_OK) != 0)
		return (false);
	return (true);
}
