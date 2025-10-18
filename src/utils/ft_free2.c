/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 14:50:57 by skuor             #+#    #+#             */
/*   Updated: 2025/10/17 19:54:48 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env **env)
{
	t_env	*current;
	t_env	*next;

	if (!env || !*env)
		return ;
	current = *env;
	while (current)
	{
		next = current->next;
		free(current->name);
		free(current->value);
		free_doublechar(current->path);
		free(current->str);
		free(current);
		current = next;
	}
	*env = NULL;
}

char	*ft_free_str(char *str)
{
	free(str);
	return (NULL);
}

void	ft_fd_test(void)
{
	int	i;

	i = 3;
	while (i < 11)
	{
		if (isatty(i) == 1)
			close(i);
		i++;
	}
}

void	close_fd(t_cmd *cmd)
{
	if (cmd->fd_int_put >= 0)
	{
		close_fds(&cmd->fd_int_put);
		cmd->fd_int_put = -2;
	}
	if (cmd->fd_out_put1 >= 0)
	{
		close_fds(&cmd->fd_out_put1);
		cmd->fd_out_put1 = -2;
	}
	if (cmd->fd_out_put2 >= 0)
	{
		close_fds(&cmd->fd_out_put2);
		cmd->fd_out_put2 = -2;
	}
	if (cmd->here >= 0)
	{
		close_fds(&cmd->here);
		cmd->here = -2;
	}
	ft_fd_test();
}
