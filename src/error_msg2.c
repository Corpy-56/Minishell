/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 16:30:30 by skuor             #+#    #+#             */
/*   Updated: 2025/10/15 11:56:41 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	err_msg_file_or_dir(char **argv, t_shell *stru)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(argv[0], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	stru->last_status = 127;
}

void	err_msg_cd(char *args)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(args, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

void	err_msg_num(char **argv, t_shell *stru)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(argv[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	stru->last_status = 2;
	stru->should_exit = 1;
}

void	err_msg_ambiguous(char *args)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(args, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
}
