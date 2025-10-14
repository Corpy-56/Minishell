/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:50:15 by skuor             #+#    #+#             */
/*   Updated: 2025/10/14 18:33:19 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_shell *stru)
{
	stru->should_exit = 0;
	stru->hdc_interrupted = 0;
	// stru->hd_abort = 0;
}

void	init_export(t_export *exp, t_env **env, t_env **local)
{
	exp->env = env;
	exp->local = local;
}
