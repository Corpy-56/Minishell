/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:01:37 by skuor             #+#    #+#             */
/*   Updated: 2025/07/23 14:15:00 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (false);
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[i])
	{
		if (!isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	

int	ft_exit(char **args)
{
	long	result;

//	result = 0;
	printf("exit\n");
	if (!args[1])
		exit(0);
	if (!is_numeric(args[1]))
	{
		printf("bash: exit: %s: numeric argument required\n", args[1]);
		exit(2);
	}
	if (args[2]) 
	{ 
		printf("bash: exit: too many arguments\n");
		return (1);
	}
	result = ft_atol(args[1]);
	exit (result % 256);
	return (0);
}

