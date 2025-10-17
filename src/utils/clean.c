/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 14:32:46 by skuor             #+#    #+#             */
/*   Updated: 2025/10/17 17:00:28 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_cmd(t_shell *stru)
{
	if (!stru)
		return ;
	if (stru->commande)
	{
		free_cmds(stru->commande);
		stru->commande = NULL;
	}
	if (stru->tokens)
	{
		free_tokens(stru->tokens);
		stru->tokens = NULL;
	}
	if (stru->exec)
	{
		free(stru->exec);
		stru->exec = NULL;
	}
	if (stru->path_dirs)
	{
		free_doublechar(stru->path_dirs);
		stru->path_dirs = NULL;
	}
}

void	clean_all(t_shell *stru)
{
	(void)stru;
	clean_cmd(stru);
	if (stru->environ)
	{
		free_env(&stru->environ);
		stru->environ = NULL;
	}
	if (stru->local)
	{
		free_env(&stru->local);
		stru->local = NULL;
	}
	if (stru->dup_0 >= 0)
		close (stru->dup_0);
	if (stru->dup_1 >= 0)
		close (stru->dup_1);
	clean_gnl();
	clear_history();
}

void	clean_env(t_shell *stru)
{
	if (!stru)
		return ;
	if (stru->environ)
	{
		free_env(&stru->environ);
		stru->environ = NULL;
	}
	if (stru->local)
	{
		free_env(&stru->local);
		stru->local = NULL;
	}
}

void	clean_children(t_shell *stru)
{
	if (!stru)
		_exit(1);
	if (stru->commande)
	{
		free_cmds(stru->commande);
		stru->commande = NULL;
	}
	if (stru->tokens)
	{
		free_tokens(stru->tokens);
		stru->tokens = NULL;
	}
	if (stru->path_dirs)
	{
		free_doublechar(stru->path_dirs);
		stru->path_dirs = NULL;
	}
	stru->path_node = NULL;
	clean_env(stru);
}

void	clean_gnl(void)
{
	(void)get_next_line(-1);
}
