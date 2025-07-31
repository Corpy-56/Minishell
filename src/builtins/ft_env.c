/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 11:07:01 by skuor             #+#    #+#             */
/*   Updated: 2025/07/31 14:06:37 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_shell *stru, char **env)
{
	stru->environ = ft_duplicate_env(env);
	while (stru->environ != NULL)
	{
		printf("%s\n", stru->environ->str);
		stru->environ = stru->environ->next;
	}
	return (0);
}
