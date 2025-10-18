/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:01:37 by skuor             #+#    #+#             */
/*   Updated: 2025/10/18 11:56:45 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_overflowing(long res, long neg, long digit)
{
	if (neg == 1)
		return (res > (LONG_MAX - digit) / 10);
	else
		return (res > (-(LONG_MIN + digit)) / 10);
}

int	str_not_digit(const char *str, long neg, int i)
{
	(void)neg;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg = -1;
		if (str[i] == '+')
			neg = 2;
		i++;
	}
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	return (neg);
}

int	str_to_long(const char *str, long *out, int i)
{
	long		neg;
	long		res;
	long		digit;

	neg = 1;
	res = 0;
	neg = str_not_digit(str, neg, i);
	if (neg == -1 || neg == 2)
		i++;
	if (neg == 2)
		neg = 1;
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
