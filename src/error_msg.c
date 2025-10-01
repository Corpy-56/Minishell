/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 12:17:23 by skuor             #+#    #+#             */
/*   Updated: 2025/10/01 14:39:48 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	err_msg_cmd(char **argv, t_shell *stru)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(argv[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	stru->last_status = 127;
}

void	err_msg_export(char *argv)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(argv, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
}

void	err_msg_syntax(char *c)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(c, 2);
	ft_putstr_fd("'\n", 2);
}

void	err_msg_dir(char **argv, t_shell *stru)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(argv[0], 2);
	ft_putstr_fd(": is a directory\n", 2);
	stru->last_status = 126;
}

void	err_msg_chdir(char **args)
{
	(void)args;
	ft_putstr_fd("chdir: error retrieving current directory: : ", 2);
	ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
	ft_putstr_fd("No such file or directory\n", 2);
}
