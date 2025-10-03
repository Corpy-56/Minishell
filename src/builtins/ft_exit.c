/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:01:37 by skuor             #+#    #+#             */
/*   Updated: 2025/10/03 16:58:22 by skuor            ###   ########.fr       */
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

void	err_msg_num(char **argv, t_shell *stru)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(argv[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	stru->last_status = 2;
	stru->should_exit = 1;
}

// int	ft_exit(t_shell *stru, char **args)
// {
// 	long	out;

// 	out = 0;
// 	printf("exit\n");
// 	if (!args[1])
// 	{
// 		stru->should_exit = 1;
// 		return (0);
// 	}
// 	if (str_to_long(args[1], &out))
// 		return (err_msg_num(args, stru), 2);
// 	if (args[2])
// 	{
// 		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
// 		stru->last_status = 1;
// 		return (1);
// 	}
// 	stru->last_status = out % 256;
// 	if (stru->last_status < 0)
// 		stru->last_status += 256;
// 	stru->should_exit = 1;
// 	return (stru->last_status);
// }

int	ft_exit(t_shell *stru, char **args, bool cmd_seule)
{
	long	out;

	out = 0;
	if (!args[1])
	{
		if (cmd_seule)
		{
			if (isatty(STDIN_FILENO))
				printf("exit\n");
			stru->should_exit = 1;
			return (0);
		}
	}
	if (str_to_long(args[1], &out))
	{
		if (cmd_seule)
		{
			if (isatty(STDIN_FILENO))
				printf("exit\n");
			err_msg_num(args, stru);
		}
		return (2);
	}
	if (args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		if (cmd_seule)
			stru->last_status = 1;
		return (1);
	}
	stru->last_status = out % 256;
	if (stru->last_status < 0)
		stru->last_status += 256;
	if (cmd_seule)
	{
		if (isatty(STDIN_FILENO))
			printf("exit\n");
		stru->should_exit = 1;
	}	
	return (stru->last_status);
}
