/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:09:43 by skuor             #+#    #+#             */
/*   Updated: 2025/08/23 17:37:41 by skuor            ###   ########.fr       */
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

void	move_var_to_env(t_env **env, t_env **local, t_env *var)
{
	t_env	*prev;
	t_env	*current;
	t_env	*last;

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

t_env	*create_local_var(char *args, t_env *local)
{
	char	*name;
	char	*value;
	t_env	*var;

	name = NULL;
	value = NULL;
	parse_args(args, &name, &value);
	if (!is_local_var(args) && !check_valid_var(name))
	{
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

char	*get_env_value(t_env *env, char *name)
{
	t_env	*current;

	if (!env || !name)
		return (NULL);
	current = env;
	while (current)
	{
		if (!current->name)
			return (NULL);
		if (ft_strcmp(current->name, name) == 0)
		{
			if (current->value)
				return (ft_strdup(current->value));
			else
				return (ft_strdup(""));
		}
		current = current->next;
	}
	return (NULL);
}

char	*expand_var(char *args, t_env *env, t_env *local)
{
	size_t	i;
	size_t	start;
	char	*str;
	char	*name;
	char	*value;
	size_t	len_str;
	char tmp[2];

	i = 0;
	str = ft_strdup("");
	len_str = ft_strlen(args);
	while (i < len_str)
	{
		if (args[i] != '$')
		{
			tmp[0] = args[i];
			tmp[1] = '\0';
			str = ft_strjoin_free(str, ft_strdup(tmp));
			i++;
			continue ;
		}
		i++;
		start = i;
		while ((i < len_str && ft_isalnum(args[i])) || args[i] == '_')
			i++;
		if (i == start)
		{
			str = ft_strjoin_free(str, ft_strdup("$"));
			continue ;
		}
		name = ft_substr(args, start, i - start);
		value = get_env_value(env, name);
		if (!value && local)
			value = get_env_value(local, name);
		if (!value)
			value = ft_strdup("");
		str = ft_strjoin_free(str, value);
		free(name);
	}
	return (str);
}

