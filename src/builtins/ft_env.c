/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 11:07:01 by skuor             #+#    #+#             */
/*   Updated: 2025/08/21 16:58:56 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_shell *stru)
{
	t_shell	*env_temp;

	env_temp = stru;
	while (env_temp->environ != NULL)
	{
		printf("%s\n", env_temp->environ->str);
		env_temp->environ = env_temp->environ->next;
	}
	return (0);
}

