/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 16:37:09 by skuor             #+#    #+#             */
/*   Updated: 2025/10/15 19:47:53 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_initialization_commande(t_cmd *commande)
{
	commande->args = NULL;
	commande->cmd = NULL;
	commande->heredoc = NULL;
	commande->here = -2;
	commande->fd_int_put = -2;
	commande->next = NULL;
	commande->fd_out_put1 = -2;
	commande->fd_out_put2 = -2;
	commande->next = NULL;
	return ;
}

void	init_split(t_split *split, t_tokens **head, t_shell *stru)
{
	split->ifs = get_env_value(stru->environ, "IFS");
	if (!split->ifs || !*split->ifs)
		split->ifs = " \t\n";
	split->prev = NULL;
	split->current = *head;
	split->last = NULL;
	split->fields = NULL;
	split->new_field = NULL;
	split->i = 0;
	split->j = 0;
	split->n_fields = 0;
	split->start = 0;
}

void	init_split_ifs(t_split *split, const char *str, const char *ifs)
{
	split->i = 0;
	split->j = 0;
	split->n_fields = 0;
	split->fields = NULL;
	split->str = str;
	split->ifs = ifs;
	if (!split->ifs || !*split->ifs)
		split->ifs = " \t\n";
}

void	init_pipes(t_pipes *pipes, t_cmd *head)
{
	pipes->i = 0;
	pipes->n = 0;
	pipes->prev_read = -1;
	pipes->last_status = 0;
	pipes->builtins = 0;
	pipes->status = 0;
	pipes->current = head;
	pipes->wait_child = 0;
	pipes->pid = 0;
	pipes->last_pid = -1;
}

void	init_copy(t_copy *copy, t_env *var, char *new_value)
{
	copy->new_val = NULL;
	copy->new_str = NULL;
	copy->name_len = ft_strlen(var->name);
	copy->val_len = ft_strlen(new_value);
}
