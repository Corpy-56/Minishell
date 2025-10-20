/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 17:02:46 by skuor             #+#    #+#             */
/*   Updated: 2025/10/20 15:16:10 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(t_cmd *commande)
{
	if (commande->args == NULL || commande->args[0] == NULL)
		return (false);
	if (ft_strncmp(commande->args[0], "pwd", 4) == 0)
		return (true);
	if (ft_strncmp(commande->args[0], "cd", 3) == 0)
		return (true);
	if (ft_strncmp(commande->args[0], "echo", 5) == 0)
		return (true);
	if (ft_strncmp(commande->args[0], "env", 4) == 0)
		return (true);
	if (ft_strncmp(commande->args[0], "exit", 5) == 0)
		return (true);
	if (ft_strncmp(commande->args[0], "unset", 5) == 0)
		return (true);
	if (ft_strncmp(commande->args[0], "export", 5) == 0)
		return (true);
	return (false);
}

int	ft_exec_builtins(t_cmd *commande, t_shell *stru, bool cmd_seule)
{
	int	status;

	status = 0;
	if (ft_strncmp(commande->cmd, "pwd", 4) == 0)
		status = ft_pwd(commande->args, stru);
	else if (ft_strncmp(commande->cmd, "cd", 3) == 0)
		status = ft_cd(commande->args, stru);
	else if (ft_strncmp(commande->cmd, "echo", 5) == 0)
		status = ft_echo(commande->args);
	else if (ft_strncmp(commande->cmd, "env", 4) == 0)
		status = ft_env(stru->environ);
	else if (ft_strncmp(commande->cmd, "exit", 5) == 0)
		status = ft_exit(stru, commande->args, cmd_seule);
	else if (ft_strncmp(commande->cmd, "unset", 5) == 0)
		status = ft_unset(stru, commande->args);
	else if (ft_strncmp(commande->cmd, "export", 5) == 0)
		status = ft_export(commande->args, &stru->environ, &stru->local, stru);
	else
		return (1);
	stru->last_status = status;
	return (status);
}

int	collect_status(pid_t pid, t_shell *stru)
{
	int	status;

	(void)stru;
	status = 0;
	waitpid(pid, &status, 0);
	return (status);
}
