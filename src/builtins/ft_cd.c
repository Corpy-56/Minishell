/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 21:35:08 by skuor             #+#    #+#             */
/*   Updated: 2025/07/16 12:22:22 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **args)
{
	// char	*pwd;
	char	*home;

	if (args[1] && ft_strncmp(args[1], "..", 3) == 0)
	{
		chdir("..");
		// pwd = getcwd(NULL, 0);
		// printf("%s\n", pwd);
	}
	else if (args[1])
	{
		chdir(args[1]);
		// pwd = getcwd(NULL, 0);
		// printf("%s\n", pwd);
	}
	else
	{
		home = getenv("HOME");
		if (!home)
			return (0);
		chdir(home);
		// pwd = getcwd(NULL, 0);
		// printf("%s\n", pwd);
	}
	return (0);
}
