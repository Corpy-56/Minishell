/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 21:35:08 by skuor             #+#    #+#             */
/*   Updated: 2025/09/24 14:13:16 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **args)
{
	char	*home;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (args[1] && ft_strncmp(args[1], "..", 3) == 0)
	{
		if (!pwd)
			err_msg_chdir();
		chdir("..");
	}
	else if (args[1])
	{
		if (chdir(args[1]) != 0)
		{
			// err_msg_dir(args);
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
