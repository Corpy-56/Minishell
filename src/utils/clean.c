/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 14:32:46 by skuor             #+#    #+#             */
/*   Updated: 2025/10/11 16:05:13 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_cmd(t_shell *stru)
{
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
	clean_gnl();
	clear_history();
}

void	clean_env(t_shell *stru)
{
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

void	clean_heredoc(t_shell *stru)
{
	clean_gnl();
	clean_cmd(stru);
	clean_env(stru);
}
