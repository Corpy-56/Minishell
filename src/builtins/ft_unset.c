/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 16:14:05 by skuor             #+#    #+#             */
/*   Updated: 2025/10/17 12:43:59 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_t_env_unset(t_env *node)
{
	free(node->name);
	free(node->value);
	free(node->str);
	free(node);
}

void	remove_var(t_shell *stru, char *var)
{
	t_unset	u;

	init_unset(&u, stru, var);
	while (u.node)
	{
		u.next = u.node->next;
		if (ft_strncmp(u.node->str, var, u.size_var) == 0
			&& u.node->str[u.size_var] == '=')
		{
			if (ft_strcmp(u.node->name, "PATH") == 0)
			{
				free_doublechar(stru->path_dirs);
				stru->path_dirs = NULL;
			}
			if (!u.prev)
				stru->environ = u.node->next;
			else
				u.prev->next = u.node->next;
			free_t_env_unset(u.node);
			u.node = u.next;
			continue ;
		}
		u.prev = u.node;
		u.node = u.next;
	}
}

int	ft_unset(t_shell *stru, char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (args[i][0] && check_valid_var(args[i]))
			remove_var(stru, args[i]);
		i++;
	}
	return (0);
}
