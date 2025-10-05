/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 21:35:08 by skuor             #+#    #+#             */
/*   Updated: 2025/10/05 16:31:39 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	chdir_args(char **args, char *oldpwd, char *pwd)
{
	if (chdir(args[1]) != 0)
	{
		err_msg_cd(args[1]);
		if (oldpwd_is_getcwd(oldpwd))
			free(oldpwd);
		return ;
	}
	if (!pwd)
	{
		err_msg_chdir(args);
		free(pwd);
	}
}

static void	chdir_home(char **args, t_shell *stru)
{
	char	*home;

	if (!args[1])
	{
		home = get_env_value(stru->environ, "HOME");
		if (!home)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return ;
		}
		chdir(home);
	}
}

int	ft_cd(char **args, t_shell *stru)
{
	char	*pwd;
	char	*oldpwd;
	char	*newpwd;

	chdir_home(args, stru);
	oldpwd = get_env_value(stru->environ, "PWD");
	if (!oldpwd)
		oldpwd = getcwd(NULL, 0);
	pwd = getcwd(NULL, 0);
	if (args[1])
		chdir_args(args, oldpwd, pwd);
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
