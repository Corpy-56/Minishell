/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 11:51:21 by skuor             #+#    #+#             */
/*   Updated: 2025/10/05 17:11:26 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	print_exported_var(t_env *env)
// {
// 	t_env	*current;

// 	current = env;
// 	while (current)
// 	{
// 		if (current->value)
// 			printf("export %s=\"%s\"\n", current->name, current->value);
// 		current = current->next;
// 	}
// }

static void	export2(t_env **env, t_env **local, char *name, char *value, t_shell *sh)
{
	t_env	*var;
	char	*val_final;

	var = find_var(*env, name);
	if (var)
	{
		if (value)
			update_env(*env, name, value, sh);
		return ;
	}
	var = find_var(*local, name);
	if (var)
	{
		if (value)
			val_final = ft_strdup(value);
		else if (var->value)
			val_final = ft_strdup(var->value);
		else
			val_final = NULL;
		move_var_to_env(env, local, var);
		update_env(*env, name, val_final, sh);
		return (free(val_final));
	}
	update_env(*env, name, value, sh);
}

int	ft_export(char **args, t_env **env, t_env **local, t_shell *stru)
{
	int		i;
	char	*name;
	char	*value;

	name = NULL;
	// if (!args[1])
	// 	return (print_exported_var(*env), 0);
	i = 0;
	while (args[++i])
	{
		parse_args(args[i], &name, &value);
		if (!check_valid_var(name))
		{
			err_msg_export(args[i]);
			free(name);
			free(value);
			return (1);
		}
		if (args[i] && i > 8000)
			ft_putstr_fd("minishell: /bin/ls/: Argument list too long\n", 2);
		export2(env, local, name, value, stru);
		free(name);
		free(value);
	}
	return (0);
}
