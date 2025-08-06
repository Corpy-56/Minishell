/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 21:35:08 by skuor             #+#    #+#             */
/*   Updated: 2025/08/06 14:32:26 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **args)
{
	char	*home;
	
	if (args[2])
	{
		printf("bash: cd: too many arguments\n");
		return (1);
	}
	if (args[1] && ft_strncmp(args[1], "..", 3) == 0)
		chdir("..");
	else if (args[1])
		chdir(args[1]);
	else
	{
		home = getenv("HOME");
		if (!home)
			return (0);
		chdir(home);
	}
	return (0);
}
