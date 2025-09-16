/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 14:32:46 by skuor             #+#    #+#             */
/*   Updated: 2025/09/16 16:02:54 by skuor            ###   ########.fr       */
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
	// if (stru->tokens)
	// {
	// 	free_args(stru->tokens->args);
	// 	stru->tokens->args = NULL;
	// }
	if (stru->tokens)
	{
		free_tokens(stru->tokens);
		stru->tokens = NULL;
	}
}

void	clean_all(t_shell *stru)
{
	// clean_cmd(stru);
	if (stru->environ)
	{
		free_env(&stru->environ);
		stru->environ = NULL;
	}
	clear_history();
	free(stru);
}
