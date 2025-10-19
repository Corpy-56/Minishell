/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 15:49:32 by skuor             #+#    #+#             */
/*   Updated: 2025/10/19 17:31:47 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	empty_env(t_shell *stru)
{
	char	*cwd;

	if (stru->environ == NULL)
	{
		cwd = getcwd(NULL, 0);
		if (cwd != NULL)
		{
			stru->environ = add_to_local(stru->environ, "PWD", cwd);
			free(cwd);
		}
		stru->environ = add_to_local(stru->environ, "SHLVL", "1");
	}
}

void	underscore_empty_env(t_cmd *cmd, t_shell *stru)
{
	int		i;
	char	*args;

	i = 0;
	if (!stru || !stru->environ || !cmd)
		return ;
	if (!cmd->args || !cmd->args[0])
		args = "env";
	else
	{
		while (cmd->args[i + 1])
			i++;
		args = cmd->args[i];
	}
	update_env(stru->environ, "_", args, stru);
}
