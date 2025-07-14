/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 19:34:55 by skuor             #+#    #+#             */
/*   Updated: 2025/07/14 21:55:24 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char *rl, char **args)
{
	int	i;
	int	no_newline;

	i = 1;
	no_newline = 0;
	if (ft_strncmp(rl, "echo", 5) == 0)
	{
		if (args[1] && ft_strncmp(args[1], "-n", 3) == 0)
		{
			no_newline = 1;
			i = 2;
		}
		while (args[i])
		{
			printf("%s", args[i]);
			if (args[i + 1])
				printf(" ");
			i++;
		}
		if (!no_newline)
			printf("\n");
	}
	return (0);
}