/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:50:15 by skuor             #+#    #+#             */
/*   Updated: 2025/10/17 15:19:47 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_shell *stru, char **env, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	stru->should_exit = 0;
	stru->hdc_interrupted = 0;
	stru->environ = ft_duplicate_env(env, stru);
	stru->tokens = NULL;
	stru->commande = NULL;
	stru->fd = -2;
	stru->dup_0 = dup(0);
	stru->dup_1 = dup(1);
	update_shlvl(stru->environ, stru);
	ft_tty(stru);
	set_shell(stru);
	static_struct(stru);
}

void	init_export(t_export *exp, t_env **env, t_env **local)
{
	exp->env = env;
	exp->local = local;
}
