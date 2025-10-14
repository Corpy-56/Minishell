/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 21:35:08 by skuor             #+#    #+#             */
/*   Updated: 2025/10/14 17:15:00 by skuor            ###   ########.fr       */
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

static void	chdir_home(t_cd *cd, char **args)
{
	if (!args[1])
	{
		if (!cd->home)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return ;
		}
		chdir(cd->home);
	}
}

static void	chdir_args(t_cd *cd, char **args, t_shell *stru)
{
	if (args[1] && ft_strncmp(args[1], "~", 3) == 0)
		chdir(cd->home);
	else if (args[1] && ft_strncmp(args[1], "-", 3) == 0)
	{
		cd->old = get_env_value(stru->environ, "OLDPWD");
		if (!cd->old)
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
			return ;
		}
		if (chdir(cd->old) != 0)
			return (err_msg_cd(cd->old));
	}
	else if (chdir(args[1]) != 0)
	{
		err_msg_cd(args[1]);
		return ;
	}
	if (!cd->pwd)
	{
		err_msg_chdir(args);
		free(cd->pwd);
	}
}

int	ft_cd(char **args, t_shell *stru)
{
	t_cd	cd;

	init_cd(&cd, stru);
	chdir_home(&cd, args);
	cd.oldpwd = get_env_value(stru->environ, "PWD");
	if (!cd.oldpwd)
		cd.oldpwd = getcwd(NULL, 0);
	cd.pwd = getcwd(NULL, 0);
	if (args[1])
		chdir_args(&cd, args, stru);
	cd.newpwd = getcwd(NULL, 0);
	if (!cd.newpwd)
	{
		if (oldpwd_is_getcwd(cd.oldpwd))
			free(cd.oldpwd);
		return (1);
	}
	if (cd.oldpwd)
		update_env(stru->environ, "OLDPWD", cd.oldpwd, stru);
	update_env(stru->environ, "PWD", cd.newpwd, stru);
	free(cd.newpwd);
	free(cd.pwd);
	return (0);
}
