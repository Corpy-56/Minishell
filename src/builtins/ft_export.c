/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 11:51:21 by skuor             #+#    #+#             */
/*   Updated: 2025/08/09 15:41:52 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_args(char **args)
{
	char	*name;
	char	*value;
	int		pos;
	int		i;
	int j;

	name = NULL;
	value = NULL;
	i = 1;
	while (args[i])
	{
		pos = -1;
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] == '=')
			{
				pos = j;
				break ;
			}
			j++;
		}
	if (pos != -1)
	{
		name = ft_substr(args[i], 0, pos);
		value = ft_strdup(args[i] + pos + 1);
		printf("Name: %s, Value: %s\n", name, value);
		
	}
	else
	{
		name = ft_strdup(args[i]);
		printf("Name: %s, Value: NULL\n", name);
		free(name);
	}
	i++;
}
	return (0);
}

int	find_in_env(t_env *env, char *name)
{
	t_env *current;
	//t_env *new_var;
	size_t	name_len;
	
	current = env;
	//new_var =
	name_len = ft_strlen(name);
	while (current)
	{
		if (ft_strncmp(current->str, name, name_len) == 0 && current->str[name_len] == '=')
			return 1; // Variable found
		current = current->next;
	}
	return 0;
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

void	print_exported_var(t_env *env)
{
	t_env *current;
	
	current = env;
	while (current)
	{
		if (current->str)
			printf("export %s\n", current->str);
		current = current->next;
	}
}

int	add

int	ft_export(char **args, t_env *env)
{
	int i;
	t_env *new_var;

	if (!args[1])
	{
		print_exported_var(env);
		return 0;
	}
	i = 1;
	while (args[i])
	{
		parse_args(args);
		if (!check_valid_var(args[i]))
		{
			printf("bash: export: '%s': not a valid identifier\n", args[i]);
			return 1;
		}
		else
		{
			if (find_in_env(env, args[i]) == 0)
			{
				new_var = malloc(sizeof(t_env));
				if (!new_var)
				{
					perror("malloc");
					return 1;
				}
				new_var->str = ft_strdup(args[i]);
				new_var->next = env;
				env = new_var;
			}
			else
			{
				printf("Variable '%s' already exists in the environment.\n", args[i]);
			}
		}
		i++;
	}
	//printf
	return 0;
}