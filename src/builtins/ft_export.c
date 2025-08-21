/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 11:51:21 by skuor             #+#    #+#             */
/*   Updated: 2025/08/21 16:59:10 by skuor            ###   ########.fr       */
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

t_env	*add_to_env(t_env *env, char *name, char *value, int exported)
{
	t_env	*last;
	t_env	*new_var;
	char	*tmp_str;

	new_var = ft_calloc(sizeof(t_env), 1);
	if (!new_var)
		return (env);
	new_var->name = ft_strdup(name);
	if (value)
		new_var->value = ft_strdup(value);
	else
		new_var->value = NULL;
	if (value)
	{
		tmp_str = ft_strjoin(name, "=");
		new_var->str = ft_strjoin(tmp_str, value);
		free(tmp_str);
	}
	else
		new_var->str = ft_strdup(name);
	new_var->exported = exported;
	new_var->next = NULL;
	if (!env)
		return (new_var);
	last = env;
	while (last->next)
		last = last->next;
	last->next = new_var;
	return (env);
}

int	ft_export(char **args, t_env **env, t_env *local)
{
	int		i;
	char	*name;
	char	*value;
	t_env	*var;

	name = NULL;
	if (!args[1])
	{
		print_exported_var(*env);
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
		var = find_var(*env, name);
		if (var)
			update_value(var, value);
		else
		{
			var = find_var(local, name);
			if (var)
			{
				mark_exported(var);
				move_var_to_env(env, &local, var);
				if (value)
					update_value(var, value);
				update_str(var);
			}
			else
				add_to_env(*env, name, value, 1);
		}
		free(name);
		i++;
	}
	return (0);
}
