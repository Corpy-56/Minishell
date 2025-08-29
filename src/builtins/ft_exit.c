/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:01:37 by skuor             #+#    #+#             */
/*   Updated: 2025/08/28 15:09:21 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_overflowing(long res, long neg, long digit)
{
	if (neg == 1)
		return (res > (LONG_MAX - digit) / 10);
	else
		return (res > (-(LONG_MIN + digit)) / 10);
}

static void	str_not_digit(const char *str, long neg, int i)
{
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
}

int	str_to_long(const char *str, long *out)
{
	int			i;
	long		neg;
	long		res;
	long		digit;

	i = 0;
	neg = 1;
	res = 0;
	str_not_digit(str, neg, i);
	if (!str[i])
		return (1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		digit = str[i] - '0';
		if (is_overflowing(res, neg, digit))
			return (1);
		res = res * 10 + digit;
		i++;
	}
	if (str[i])
		return (1);
	*out = res * neg;
	return (0);
}

int	ft_exit(char **args)
{
	long	out;

	printf("exit\n");
	if (!args[1])
		exit(0);
	if (str_to_long(args[1], &out))
	{
		printf("bash: exit: %s: numeric argument required\n", args[1]);
		exit(2);
	}
	if (args[2])
	{
		printf("bash: exit: too many arguments\n");
		return (1);
	}
	exit(out % 256);
	return (0);
}
