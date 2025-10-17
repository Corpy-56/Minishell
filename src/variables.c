/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:09:43 by skuor             #+#    #+#             */
/*   Updated: 2025/10/17 19:33:07 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*add_to_local(t_env *local, char *name, char *value)
{
	t_env	*last;
	t_env	*new_var;

	new_var = ft_calloc(sizeof(t_env), 1);
	if (!new_var)
		return (local);
	new_var->name = ft_strdup(name);
	if (value)
		new_var->value = ft_strdup(value);
	else
		new_var->value = NULL;
	new_var->next = NULL;
	if (!local)
		return (new_var);
	last = local;
	while (last->next)
		last = last->next;
	last->next = new_var;
	return (local);
}

static void	move_var_to_env2(t_env **env, t_env *current)
{
	t_env	*last;

	current->next = NULL;
	last = *env;
	if (!last)
		*env = current;
	else
	{
		while (last->next)
			last = last->next;
		last->next = current;
	}
}

void	move_var_to_env(t_env **env, t_env **local, t_env *var)
{
	t_env	*prev;
	t_env	*current;

	prev = NULL;
	current = *local;
	while (current && current != var)
	{
		prev = current;
		current = current->next;
	}
	if (!current)
		return ;
	if (prev)
		prev->next = current->next;
	else
		*local = current->next;
	move_var_to_env2(env, current);
}

t_env	*create_local_var(char *args, t_env *local, t_shell *stru)
{
	char	*name;
	char	*value;
	t_env	*var;

	name = NULL;
	value = NULL;
	parse_args(args, &name, &value);
	if (!is_assignment_word(args))
	{
		err_msg_cmd(&args, stru);
		free(name);
		free(value);
		return (local);
	}
	var = find_var(local, name);
	if (var)
	{
		if (update_value(var, value) == -1)
			ft_putstr_fd("Error value\n", 2);
	}
	else
		local = add_to_local(local, name, value);
	free(name);
	free(value);
	return (local);
}
