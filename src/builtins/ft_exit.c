/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:01:37 by skuor             #+#    #+#             */
/*   Updated: 2025/10/12 14:58:08 by skuor            ###   ########.fr       */
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
	(void)neg;
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

void	print_exit(bool cmd_seule)
{
	if (cmd_seule && isatty(STDIN_FILENO))
		printf("exit\n");
}

static void	exit_fin(t_shell *stru, bool cmd_seule)
{
	print_exit(cmd_seule);
	if (cmd_seule)
		stru->should_exit = 1;
}

static int	exit_badnum(t_shell *stru, char **args, bool cmd_seule)
{
	print_exit(cmd_seule);
	if (cmd_seule)
		err_msg_num(args, stru);
	return (2);
}

static int	exit_too_many(t_shell *stru, bool cmd_seule)
{
	print_exit(cmd_seule);
	ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	if (cmd_seule)
		stru->last_status = 1;
	return (1);
}

int	ft_exit(t_shell *stru, char **args, bool cmd_seule)
{
	long	out;

	out = 0;
	if (!args[1])
	{
		print_exit(cmd_seule);
		if (cmd_seule)
			stru->should_exit = 1;
		return (stru->last_status);
	}
	if (str_to_long(args[1], &out))
		return (exit_badnum(stru, args, cmd_seule));
	if (args[2])
		return (exit_too_many(stru, cmd_seule));
	stru->last_status = out % 256;
	if (stru->last_status < 0)
		stru->last_status += 256;
	exit_fin(stru, cmd_seule);
	return (stru->last_status);
}
