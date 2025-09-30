/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 14:32:46 by skuor             #+#    #+#             */
/*   Updated: 2025/09/30 15:25:36 by skuor            ###   ########.fr       */
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
	clear_history();
}
