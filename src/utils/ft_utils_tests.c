/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_tests.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:56:23 by agouin            #+#    #+#             */
/*   Updated: 2025/10/01 16:22:43 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_test_no_errors(t_cmd *commande)
{
	t_cmd	*a;

	a = commande;
	while (a)
	{
		if (a->fd_int_put == -1 || a->fd_out_put1 == -1 || a->fd_out_put2 == -1)
			return (NULL);
		a = a->next;
	}
	return (commande);
}
