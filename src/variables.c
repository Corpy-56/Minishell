/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:09:43 by skuor             #+#    #+#             */
/*   Updated: 2025/08/27 19:02:43 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*add_to_list(t_env *local, char *name, char *value)
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
	current->exported = 1;
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

int	is_assignment_word(const char *str)
{
	const char	*next;
	const char	*eq_sign;

	eq_sign = ft_strchr(str, '=');
	if (!eq_sign || eq_sign == str)
		return (0);
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	next = str + 1;
	while (next < eq_sign)
	{
		if (!ft_isalnum(*next) && *next != '_')
			return (0);
		next++;
	}
	return (1);
}


t_env	*create_local_var(char *args, t_env *local)
{
	char	*name;
	char	*value;
	t_env	*var;

	name = NULL;
	value = NULL;
	parse_args(args, &name, &value);
	if (!is_assignment_word(args))
	{
		printf("bash: '%s': command not found\n", args);
		free(name);
		free(value);
		return (local);
	}
	var = find_var(local, name);
	if (var)
		update_value(var, ft_strdup(value));
	else
		local = add_to_list(local, name, value);
	free(name);
	free(value);
	return (local);
}


int	main_variables(t_shell *stru)
{
	int		i;

	i = 0;
	if (stru->tokens->args[0] && is_assignment_word(stru->tokens->args[0]))
	{
		while (stru->tokens->args[i]
			&& is_assignment_word(stru->tokens->args[i]))
		{
			stru->local = create_local_var(stru->tokens->args[i], stru->local);
			i++;
		}
		if (stru->tokens->args[i] == NULL)
		{
			free_tokens(stru->tokens);
			stru->tokens = NULL;
			return (1);
		}
	}
	return (0);
}




