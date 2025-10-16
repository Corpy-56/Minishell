/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 12:32:05 by skuor             #+#    #+#             */
/*   Updated: 2025/10/16 16:14:17 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_args(char *args, char **name, char **value)
{
	int		pos;
	int		j;

	pos = -1;
	j = -1;
	while (args[++j])
	{
		if (args[j] == '=')
		{
			pos = j;
			break ;
		}
	}
	if (pos != -1)
	{
		*name = ft_substr(args, 0, pos);
		*value = ft_strdup(args + pos + 1);
	}
	else
	{
		*name = ft_strdup(args);
		*value = NULL;
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

t_env	*find_var(t_env *env, char *name)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	no_new_value(t_copy *copy, t_env *var)
{
	copy->new_str = ft_strdup(var->name);
	if (!copy->new_str)
		return ;
}

int	update_value(t_env *var, char *new_value)
{
	t_copy	copy;

	init_copy(&copy, var, new_value);
	if (new_value)
	{
		copy.new_val = ft_strdup(new_value);
		if (!copy.new_val)
			return (-1);
		copy.new_str = malloc((copy.name_len + 1) + (copy.val_len + 1));
		if (!copy.new_str)
			return (free(copy.new_val), -1);
		ft_memcpy(copy.new_str, var->name, copy.name_len);
		copy.new_str[copy.name_len] = '=';
		ft_memcpy((copy.new_str + copy.name_len + 1), new_value, copy.val_len);
		copy.new_str[copy.name_len + 1 + copy.val_len] = '\0';
	}
	else
		no_new_value(&copy, var);
	free(var->value);
	free(var->str);
	var->value = copy.new_val;
	var->str = copy.new_str;
	return (0);
}
