/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 16:14:05 by skuor             #+#    #+#             */
/*   Updated: 2025/08/09 12:42:12 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* int	check_valid_var(char *str)
{
	int	i;

	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (1);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
} */

void	remove_var(t_shell *stru, char *var)
{
	t_env	*prev;
	t_env	*node;
	int		size_var;

	node = stru->environ;
	size_var = ft_strlen(var);
	while (node)
	{
		if (ft_strncmp(node->str, var, size_var) == 0
			&& node->str[size_var] == '=')
		{
			if (!prev)
				stru->environ = node->next;
			else
				prev->next = node->next;
			free(node->str);
			free(node);
		}
		prev = node;
		node = node->next;
	}
}


int	ft_unset(t_shell *stru, char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (check_valid_var(args[i]))
		{
			//printf("Error\n");
			remove_var(stru, args[i]);
		}
		i++;
	}
	return 0;
}