/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:50:15 by skuor             #+#    #+#             */
/*   Updated: 2025/10/19 16:40:35 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_shell *stru, char **env, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	stru->status = 0;
	stru->should_exit = 0;
	stru->environ = ft_duplicate_env(env, stru);
	stru->tokens = NULL;
	stru->commande = NULL;
	stru->fd = -2;
	stru->dup_0 = dup(0);
	stru->dup_1 = dup(1);
	if (stru->dup_0 == -1 || stru->dup_1 == -1)
		return ;
	empty_env(stru);
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

void	init_unset(t_unset *u, t_shell *stru, char *var)
{
	u->prev = NULL;
	u->node = stru->environ;
	u->next = NULL;
	u->size_var = ft_strlen(var);
}

void	init_type(t_type *t, t_tokens *b_debut)
{
	t->a_debut = NULL;
	t->fin = NULL;
	t->i = 0;
	t->p_actuel = b_debut;
}

void	init_dupenv(t_dupenv *d)
{
	d->a_debut = NULL;
	d->fin = NULL;
	d->new = NULL;
	d->i = 0;
}
