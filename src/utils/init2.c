/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:16:20 by skuor             #+#    #+#             */
/*   Updated: 2025/10/09 16:51:41 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_tab(t_tab *tab, t_env *env)
{
	tab->envp = NULL;
	tab->line = NULL;
	tab->n_nodes = count_nodes(env);
	tab->i = 0;
	tab->node = env;
}

void	init_exec(t_exec *exec, t_shell *stru)
{
	exec->head = stru->commande;
	exec->builtins = 0;
	exec->n = count_maillons(exec->head);
	exec->fd_stdin = dup(0);
	exec->fd_stdout = dup(1);
	exec->fd = 0;
}
