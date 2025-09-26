/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 21:35:08 by skuor             #+#    #+#             */
/*   Updated: 2025/09/26 19:50:25 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	err_msg_cd(char *args)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(args, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

// int	ft_cd(char **args, t_shell *stru)
// {
// 	char	*home;
// 	char	*pwd;
// 	(void)stru;

// 	pwd = getcwd(NULL, 0);
// 	if (args[1] && ft_strncmp(args[1], "..", 3) == 0)
// 	{
// 		if (!pwd)
// 			err_msg_chdir();
// 		chdir("..");
// 	}
// 	else if (args[1])
// 	{
// 		if (chdir(args[1]) != 0)
// 		{
// 			err_msg_cd(args[1]);
// 			return (1);
// 		}
// 		chdir(args[1]);
// 	}
// 	else
// 	{
// 		home = getenv("HOME");
// 		if (!home)
// 			return (1);
// 		chdir(home);
// 	}
// 	return (0);
// }


// int	ft_cd(char **args, t_shell *stru)
// {
// 	char	*home;
// 	char	*pwd;
// 	char	*oldpwd;
// 	char	*newpwd;
	
// 	pwd = getcwd(NULL, 0);
// 	if (args[1] && ft_strncmp(args[1], "..", 3) == 0)
// 	{
// 		if (!pwd)
// 			err_msg_chdir();
// 		chdir("..");
// 	}
// 	else if (args[1])
// 	{
// 		// if (chdir(args[1]) != 0)
// 		// {
// 		// 	err_msg_cd(args[1]);
// 		// 	return (1);
// 		// }
// 		// chdir(args[1]);
// 		oldpwd = get_env_value(stru->environ, "PWD");
// 		if (!oldpwd)
// 			oldpwd = getcwd(NULL, 0);
// 		if (chdir(args[1]) != 0)
// 		{
// 			err_msg_cd(args[1]);
// 			if (!oldpwd)
// 				free(oldpwd);
// 			return (1);
// 		}
// 		newpwd = getcwd(NULL, 0);
// 		if (!newpwd)
// 		{
// 			if (!oldpwd)
// 				free(oldpwd);
// 			return (1);
// 		}
// 		if (oldpwd)
// 			update_env(stru->environ, "OLDPWD", oldpwd, stru);
// 		update_env(stru->environ, "PWD", newpwd, stru);
// 		if (!oldpwd)
// 			free(oldpwd);
// 		free(newpwd);
		
// 	}
// 	else
// 	{
// 		home = get_env_value(stru->environ, "HOME");
// 		if (!home)
// 		{
// 			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
// 			return (1);
// 		}
// 		chdir(home);
// 	}
// 	return (0);
// }

int	ft_cd(char **args, t_shell *stru)
{
	char	*home;
	char	*pwd;
	char	*oldpwd;
	char	*newpwd;
	
	pwd = getcwd(NULL, 0);
	if (!args[1])
	{
		home = get_env_value(stru->environ, "HOME");
		if (!home)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
	}
	oldpwd = get_env_value(stru->environ, "PWD");
	if (!oldpwd)
		oldpwd = getcwd(NULL, 0);
	if (chdir(args[1]) != 0)
	{
		err_msg_cd(args[1]);
		if (!oldpwd)
			free(oldpwd);
		return (1);
	}
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
	{
		if (!oldpwd)
			free(oldpwd);
		return (1);
	}
	if (oldpwd)
		update_env(stru->environ, "OLDPWD", oldpwd, stru);
	update_env(stru->environ, "PWD", newpwd, stru);
	if (!oldpwd)
		free(oldpwd);
	free(newpwd);
	return (0);
}