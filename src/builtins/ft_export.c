/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 11:51:21 by skuor             #+#    #+#             */
/*   Updated: 2025/10/16 20:11:37 by skuor            ###   ########.fr       */
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

static int	set_in_env(t_export *exp, char *name, char *val, t_shell *sh)
{
	t_env	*var;

	var = find_var(*exp->env, name);
	if (!var)
		return (0);
	if (val)
		update_env(*exp->env, name, val, sh);
	return (1);
}

static int	set_from_local(t_export *exp, char *name, char *val, t_shell *stru)
{
	t_env	*var;
	char	*val_final;

	var = find_var(*exp->local, name);
	if (!var)
		return (0);
	if (val)
		val_final = ft_strdup(val);
	else if (var->value)
		val_final = ft_strdup(var->value);
	else
		val_final = NULL;
	move_var_to_env(exp->env, exp->local, var);
	update_env(*exp->env, name, val_final, stru);
	return (free(val_final), 1);
}

static int	export_one(t_export *exp, char *args, t_shell *stru)
{
	char	*name;
	char	*value;

	parse_args(args, &name, &value);
	if (!check_valid_var(name))
	{
		err_msg_export(args);
		free(name);
		free(value);
		return (1);
	}
	if (set_in_env(exp, name, value, stru)
		|| set_from_local(exp, name, value, stru))
	{
		free(name);
		free(value);
		return (0);
	}
	update_env(*exp->env, name, value, stru);
	free(name);
	free(value);
	return (0);
}

int	ft_export(char **args, t_env **env, t_env **local, t_shell *stru)
{
	t_export	exp;
	int			i;

	init_export(&exp, env, local);
	if (!args[1])
		return (print_exported_var(*env), 0);
	i = 1;
	while (args[i])
	{
		if (args[i] && i > 8000)
			ft_putstr_fd("minishell: /bin/ls/: Argument list too long\n", 2);
		if (export_one(&exp, args[i], stru))
			return (1);
		i++;
	}
	return (0);
}
