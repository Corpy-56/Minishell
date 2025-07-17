/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:01:37 by skuor             #+#    #+#             */
/*   Updated: 2025/07/17 16:24:42 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char **args)
{
	int	result;

	result = 0;
	printf("exit\n");
	if (args[1] && isdigit(*args[1]))
	{
		if (ft_atoi(args[1]) > 255)
		{
			result = ft_atoi(args[1]) % 256;
			exit(result);
		}
		else
			exit(ft_atoi(args[1]));
	}
	else if (args[1] && !isdigit(*args[1]))
	{
		printf("bash: exit: %s: numeric argument required\n", args[1]);
		exit(2);
	}
	else if (args[2])
		printf("bash: exit: too many arguments\n");
	else
		exit(EXIT_SUCCESS);
	return (0);
}


