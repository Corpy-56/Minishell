/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 21:35:08 by skuor             #+#    #+#             */
/*   Updated: 2025/09/29 16:40:39 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	err_msg_cd(char *args)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(args, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

static bool	oldpwd_is_getcwd(char *oldpwd)
{
	if (oldpwd)
	{
		oldpwd = getcwd(NULL, 0);
		return (true);
	}
	free(oldpwd);
	return (false);
}

int	ft_cd(char **args, t_shell *stru)
{
	char	*home;
	char	*pwd;
	char	*oldpwd;
	char	*newpwd;

	if (!args[1])
	{
		home = get_env_value(stru->environ, "HOME");
		if (!home)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
		chdir(home);
	}
	oldpwd = get_env_value(stru->environ, "PWD");
	if (!oldpwd)
		oldpwd = getcwd(NULL, 0);
	pwd = getcwd(NULL, 0);
	if (args[1])
	{
		if (chdir(args[1]) != 0)
		{
			err_msg_cd(args[1]);
			if (oldpwd_is_getcwd(oldpwd))
				free(oldpwd);
			return (1);
		}
		if (!pwd)
		{
			err_msg_chdir();
			free(pwd);
		}
	}
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
	{
		if (oldpwd_is_getcwd(oldpwd))
			free(oldpwd);
		return (1);
	}
	if (oldpwd)
		update_env(stru->environ, "OLDPWD", oldpwd, stru);
	update_env(stru->environ, "PWD", newpwd, stru);
	free(newpwd);
	free(pwd);
	return (0);
}
