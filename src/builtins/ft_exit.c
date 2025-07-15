/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:01:37 by skuor             #+#    #+#             */
/*   Updated: 2025/07/15 16:29:24 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char **args)
{
	printf("exit\n");
	exit(EXIT_SUCCESS);
	if (!isdigit(*args[1]))
	{
		printf("bash: exit: %s: numeric argument required\n", args[1]);
		exit(EXIT_SUCCESS);
	}
	return (0);
}


