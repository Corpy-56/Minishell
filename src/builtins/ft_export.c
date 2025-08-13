/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 11:51:21 by skuor             #+#    #+#             */
/*   Updated: 2025/08/13 18:44:28 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	print_exported_var(t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (current->str)
			printf("export %s\n", current->str);
		current = current->next;
	}
}

/* t_env	*add_to_env(t_env *env, char *name, char *value)
{
	t_env	*last;
	t_env	*new_var;
	char	*full_str;
	char	*tmp_str;

	last = env;
	if (value)
	{
		tmp_str = ft_strjoin(name, "=");
		full_str = ft_strjoin(tmp_str, value);
	}
	else
		full_str = ft_strdup(name);
	new_var = ft_calloc(sizeof(t_env), 1);
	if (!new_var)
		return (env);
	new_var->str = full_str;
	new_var->next = NULL;
	if (!env)
		return (new_var);
	while (last->next)
		last = last->next;
	last->next = new_var;
	return (env);
} */
t_env	*add_to_env(t_env *env, char *name, char *value, int exported)
{
	t_env	*last;
	t_env	*new_var;
	char	*full_str;
	char	*tmp_str;

	last = env;
	new_var->name = ft_strdup(name);
	new_var->value = ft_strdup(value);
	if (value)
	{
		tmp_str = ft_strjoin(name, "=");
		full_str = ft_strjoin(tmp_str, value);
	}
	else
		full_str = ft_strdup(name);
	new_var = ft_calloc(sizeof(t_env), 1);
	if (!new_var)
		return (env);
	new_var->str = full_str;
	new_var->next = NULL;
	if (!env)
		return (new_var);
	while (last->next)
		last = last->next;
	last->next = new_var;
	return (env);
}

int	ft_export(char **args, t_env *env)
{
	int		i;
	char	*name;
	char	*value;
	t_env	*var;

	name = NULL;
	if (!args[1])
	{
		print_exported_var(env);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		parse_args(args[i], &name, &value);
		if (!check_valid_var(name))
		{
			printf("bash: export: '%s': not a valid identifier\n", args[i]);
			free(name);
			free(value);
			return (1);
		}
		var = find_in_env(env, name);
		if (var)
			update_value(var, name, value);
		else
			add_to_env(env, name, value);
		free(name);
	//	free(value);
		i++;
	}
	return (0);
}
