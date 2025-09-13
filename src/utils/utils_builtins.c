/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 17:02:46 by skuor             #+#    #+#             */
/*   Updated: 2025/09/13 17:53:06 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(t_cmd *commande)
{
	if (commande->args[0] == NULL)
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
