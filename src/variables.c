/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:09:43 by skuor             #+#    #+#             */
/*   Updated: 2025/08/13 17:22:43 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*local_var(t_env *local, char *name, char *value)
{
	t_env	*last;
	t_env	*new_var;
	char	*full_str;
	char	*tmp_str;

	last = local;
	if (value)
	{
		tmp_str = ft_strjoin(name, "=");
		full_str = ft_strjoin(tmp_str, value);
	}
	else
		full_str = ft_strdup(name);
	new_var = ft_calloc(sizeof(t_env), 1);
	if (!new_var)
		return (local);
	new_var->str = full_str;
	new_var->next = NULL;
	if (!local)
		return (new_var);
	while (last->next)
		last = last->next;
	last->next = new_var;
	return (local);
}

t_env	*create_local_var(char **args, t_env *local)
{
	int		i;
	char	*name;
	char	*value;
	t_env	*var;

	i = 0;
	while (args[i])
	{
		parse_args(args[i], &name, &value);
		if (!check_valid_var(name))
		{
			printf("%s: command not found\n", args[i]);
			free(name);
			free(value);
			return (NULL);
		}
		var = find_in_env(local, name);
		if (var)
			update_value(local, name, value);
		else
			local = local_var(local, name, value);
		free(name);
		free(value);
		i++;
	}
	return (local);
}

char	*get_env_value(t_env *env, char *name)
{
	t_env	*current;
	size_t	name_len;
	//char	*value;

	if (!env || !name)
    	return (NULL);
	current = env;
	name_len = ft_strlen(name);
//	value = ft_strdup(current->str + name_len + 1);
	while (current)
	{
		if (ft_strncmp(current->str, name, name_len) == 0
			&& current->str[name_len] == '=')
			return (ft_strdup(current->str + name_len + 1));
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

	i = 0;
	str = ft_strdup("");
	len_str = ft_strlen(args);
	while (i < len_str)
	{
		if (args[i] == '$')
		{
			i++;
			start = i;
			while (i < len_str && check_valid_var(&args[i]))
				i++;
			if (i > start)
			{
				name = ft_substr(args, start, i - start);
				value = get_env_value(env, name);
				if (!value && local)
					value = get_env_value(local, name);
				if (!value)
					value = ft_strdup("");
				str = ft_strjoin_free(str, value);
				free(name);
			}
			else
				str = ft_strjoin_free(str, ft_strdup("$"));
		}
		else
		{
			auto char tmp[2] = {args[i], '\0'};
			str = ft_strjoin_free(str, ft_strdup(tmp));
			i++;
		}
	}
	return (str);
}

