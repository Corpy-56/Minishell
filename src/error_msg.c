/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 12:17:23 by skuor             #+#    #+#             */
/*   Updated: 2025/09/19 16:33:38 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	err_msg_cmd(char **argv)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(argv[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
}

void	err_msg_export(char *argv)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(argv, 2);
	ft_putstr_fd(": not a valid identifiier\n", 2);
}

void	err_msg_synt(char *c)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(c, 2);
	ft_putstr_fd("'\n", 2);
	// return (-1);
}
