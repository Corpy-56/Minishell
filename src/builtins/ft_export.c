/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 11:51:21 by skuor             #+#    #+#             */
/*   Updated: 2025/08/28 15:07:19 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_exported_var(t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (current->value)
			printf("export %s=\"%s\"\n", current->name, current->value);
		current = current->next;
	}
}

t_env	*add_to_env2(t_env *env, char *name, char *value, t_env *new_var)
{
	char	*tmp_str;
	t_env	*last;

	if (value)
	{
		tmp_str = ft_strjoin(name, "=");
		new_var->str = ft_strjoin(tmp_str, value);
		free(tmp_str);
	}
	else
		new_var->str = ft_strdup(name);
	new_var->next = NULL;
	if (!env)
		return (new_var);
	last = env;
	while (last->next)
		last = last->next;
	last->next = new_var;
	return (new_var);
}

t_env	*add_to_env(t_env *env, char *name, char *value)
{
	t_env	*new_var;

	new_var = ft_calloc(sizeof(t_env), 1);
	if (!new_var)
		return (env);
	new_var->name = ft_strdup(name);
	if (value)
		new_var->value = ft_strdup(value);
	else
		new_var->value = NULL;
	add_to_env2(env, name, value, new_var);
	return (env);
}

static void	export2(t_env **env, t_env **local, char *name, char *value)
{
	t_env	*var;

	var = find_var(*env, name);
	if (var)
		update_value(var, value);
	else
	{
		var = find_var(*local, name);
		if (var)
		{
			move_var_to_env(env, local, var);
			if (value)
				update_value(var, value);
			update_str(var);
		}
		else
			*env = add_to_env(*env, name, value);
	}
}

int	ft_export(char **args, t_env **env, t_env **local)
{
	int		i;
	char	*name;
	char	*value;

	name = NULL;
	if (!args[1])
		return (print_exported_var(*env), 0);
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
		export2(env, local, name, value);
		free(name);
		free(value);
		i++;
	}
	return (0);
}
