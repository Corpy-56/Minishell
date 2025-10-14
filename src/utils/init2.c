/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:16:20 by skuor             #+#    #+#             */
/*   Updated: 2025/10/14 14:42:41 by skuor            ###   ########.fr       */
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
	exec->status = 0;
	exec->n = count_maillons(exec->head);
	exec->fd_stdin = -1;
	exec->fd_stdout = -1;
	exec->fd = 0;
}

void	init_cd(t_cd *cd, t_shell *stru)
{
	cd->home = get_env_value(stru->environ, "HOME");
	cd->oldpwd = NULL;
	cd->newpwd = NULL;
	cd->pwd = NULL;
	cd->old = NULL;
}

void	init_ext(t_ext *ext, t_cmd *cmd)
{
	ext->argv = cmd->args;
	ext->envp = NULL;
	ext->chosen_path = NULL;
}

void	init_expand(t_expand *exp, t_tokens *tk, size_t i)
{
	exp->str = tk->str;
	exp->len_str = ft_strlen(exp->str);
	exp->out = ft_calloc(1, 1);
	exp->start = i;
	exp->j = 0;
}
