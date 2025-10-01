/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 21:35:08 by skuor             #+#    #+#             */
/*   Updated: 2025/08/27 18:03:25 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **args)
{
	char	*home;

	if (args[1] && ft_strncmp(args[1], "..", 3) == 0)
		chdir("..");
	else if (args[1])
	{
		if (chdir(args[1]) != 0)
		{
			printf("bash: cd: %s: No such file or directory\n", args[1]);
			return (1);
		}
		chdir(args[1]);
	}
	else
	{
		home = getenv("HOME");
		if (!home)
			return (1);
		chdir(home);
	}
	return (0);
}
