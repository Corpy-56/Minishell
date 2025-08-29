/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 12:32:05 by skuor             #+#    #+#             */
/*   Updated: 2025/08/28 14:49:09 by skuor            ###   ########.fr       */
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
		printf("Name: %s, Value: %s\n", *name, *value);
	}
	else
	{
		*name = ft_strdup(args);
		*value = NULL;
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

void	update_value(t_env *var, char *new_value)
{
	char	*tmp_str;

	free(var->value);
	if (new_value)
		var->value = ft_strdup(new_value);
	else
		var->value = NULL;
	free(var->str);
	if (var->value)
	{
		tmp_str = ft_strjoin(var->name, "=");
		var->str = ft_strjoin(tmp_str, new_value);
	}
	else
		var->str = ft_strdup(var->name);
}

void	update_str(t_env *var)
{
	char	*tmp;

	if (!var)
		return ;
	if (var->str)
		free(var->str);
	if (var->value)
	{
		tmp = ft_strjoin(var->name, "=");
		var->str = ft_strjoin(tmp, ft_strdup(var->value));
	}
	else
		var->str = ft_strdup(var->name);
}
