/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 12:32:05 by skuor             #+#    #+#             */
/*   Updated: 2025/08/12 15:34:58 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_args(char *args, char **name, char **value)
{
	int		pos;
	int		j;

	pos = -1;
	j = 0;
	while (args[j])
	{
		if (args[j] == '=')
		{
			pos = j;
			break ;
		}
			j++;
	}
	if (pos != -1)
	{
		*name = ft_substr(args, 0, pos);
		*value = ft_strdup(args + pos + 1);
		printf("Name: %s, Value: %s\n", *name, *value);
	}
	else
	{
		*name = ft_strdup(args);
		printf("Name: %s, Value: NULL\n", *name);
	}
}

int	check_valid_var(char *str)
{
	int	i;

	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

t_env	*find_in_env(t_env *env, char *name)
{
	t_env	*current;
	size_t	name_len;

	current = env;
	name_len = ft_strlen(name);
	while (current)
	{
		if (ft_strncmp(current->str, name, name_len) == 0
			&& current->str[name_len] == '=')
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	update_value(t_env *var, char *name, char *new_value)
{
	t_env	*node;
	char	*tmp_str;

	node = find_in_env(var, name);
	if (!node)
		return ;
	tmp_str = ft_strjoin(name, "=");
	free(var->str);
	node->str = ft_strjoin(tmp_str, new_value);
	free(tmp_str);
}

