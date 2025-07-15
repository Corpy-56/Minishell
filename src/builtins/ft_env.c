/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 11:07:01 by skuor             #+#    #+#             */
/*   Updated: 2025/07/15 16:31:22 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_shell *stru)
{
	int	i;

	i = 0;
	while (stru->environ != NULL)
	{
		printf("%s\n", stru->environ->str);
		stru->environ = stru->environ->next;
	}
	return (0);
}
