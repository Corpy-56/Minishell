/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:50:15 by skuor             #+#    #+#             */
/*   Updated: 2025/10/16 18:06:47 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_shell *stru, char **env)
{
	stru->should_exit = 0;
	stru->hdc_interrupted = 0;
	stru->environ = ft_duplicate_env(env, stru);
	stru->tokens = NULL;
	stru->commande = NULL;
	stru->fd = -2;
	update_shlvl(stru->environ, stru);
	// save_termios1();
	ft_tty(stru);
	set_shell(stru);
	static_struct(stru);
}

void	init_export(t_export *exp, t_env **env, t_env **local)
{
	exp->env = env;
	exp->local = local;
}
