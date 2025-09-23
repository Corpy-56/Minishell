/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expan.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 14:47:22 by skuor             #+#    #+#             */
/*   Updated: 2025/09/23 14:21:31 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_env *env, char *name)
{
	t_env	*current;

	if (!env || !name)
		return (NULL);
	current = env;
	while (current)
	{
		if (!current->name)
			return (NULL);
		if (ft_strcmp(current->name, name) == 0)
		{
			if (current->value)
				return (current->value);
			else
				return ("");
		}
		current = current->next;
	}
	return (NULL);
}

int	is_assignment_word(const char *str)
{
	const char	*next;
	const char	*eq_sign;

	eq_sign = ft_strchr(str, '=');
	if (!eq_sign || eq_sign == str)
		return (0);
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	next = str + 1;
	while (next < eq_sign)
	{
		if (!ft_isalnum(*next) && *next != '_')
			return (0);
		next++;
	}
	return (1);
}

// void	command_expand(t_cmd *cmd, t_shell *stru)
// {
// 	char	*expanded;
// 	int		i;

// 	i = 0;
// 	while (cmd->args[i])
// 	{
// 		expanded = expand_var(cmd->args[i], stru);
// 		if (expanded != cmd->args[i])
// 			free(cmd->args[i]);
// 		cmd->args[i] = expanded;
// 		i++;
// 	}
// }

int	extract_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

bool	is_ifs(char c, const char *ifs)
{
	int	i;
	
	i = 0;
	if (!ifs)
		return (false);
	while (ifs[i])
	{
		if (ifs[i] == c)
			return (true);
		i++;
	}
	return (false);
}

