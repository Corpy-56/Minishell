/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:01:37 by skuor             #+#    #+#             */
/*   Updated: 2025/07/11 11:26:36 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char *rl, char **args)
{

	if (ft_strncmp(rl, "exit", 4) == 0)
	{
		printf("exit\n");
		exit(EXIT_SUCCESS);
		if (!isdigit(*args[1]))
		{
			printf("bash: exit: %s: numeric argument required\n", args[1]);
			exit(EXIT_SUCCESS);
		}
	}
	return (0);
}


