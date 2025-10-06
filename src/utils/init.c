/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 16:37:09 by skuor             #+#    #+#             */
/*   Updated: 2025/10/06 10:07:48 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_initialization_commande(t_cmd *commande)
{
	commande->args = NULL;
	commande->cmd = NULL;
	commande->heredoc = NULL;
	commande->fd_int_put = -2;
	commande->next = NULL;
	commande->fd_out_put1 = -2;
	commande->fd_out_put2 = -2;
	commande->next = NULL;
	return ;
}

// void 	ft_init_fd1(void)
// {
// 	fd = ft_calloc(1, sizeof(t_fd));
// 	fd->fd_in = dup(0);
// 	fd->fd_out = dup (1);
// 	fd->fd = 5;
// 	fd->fd_out_put1 = -2;
// 	fd->fd_out_put2 = -2;
// 	fd->fd_int_put = -2;
// }


