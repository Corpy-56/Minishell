/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:50:15 by skuor             #+#    #+#             */
/*   Updated: 2025/10/15 14:10:00 by skuor            ###   ########.fr       */
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
}

void	init_export(t_export *exp, t_env **env, t_env **local)
{
	exp->env = env;
	exp->local = local;
}
