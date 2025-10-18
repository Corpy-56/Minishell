/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:52:31 by agouin            #+#    #+#             */
/*   Updated: 2025/10/17 19:57:31 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_env_node(char *str)
{
	t_env	*new;
	char	*equal;

	new = ft_calloc(sizeof(t_env), 1);
	if (!new)
		return (NULL);
	equal = ft_strchr(str, '=');
	new->str = ft_strdup(str);
	if (equal)
	{
		new->name = ft_substr(str, 0, equal - str);
		new->value = ft_strdup(equal + 1);
	}
	else
	{
		new->name = ft_strdup(str);
		new->value = NULL;
	}
	new->next = NULL;
	return (new);
}

t_env	*ft_duplicate_env(char **env, t_shell *stru)
{
	t_dupenv	d;

	init_dupenv(&d);
	stru->path_node = NULL;
	stru->path_dirs = NULL;
	while (env[d.i])
	{
		d.new = create_env_node(env[d.i]);
		if (!d.new)
			return (NULL);
		if (d.a_debut == NULL)
			d.a_debut = d.new;
		else
			d.fin->next = d.new;
		d.fin = d.new;
		if (stru->path_node == NULL
			&& ft_strncmp(d.new->name, "PATH", 5) == 0 && d.new->value != NULL )
		{
			stru->path_node = d.new;
			stru->path_dirs = ft_split(d.new->value, ':');
		}
		d.i++;
	}
	return (d.a_debut);
}

void	update_shlvl(t_env *env, t_shell *stru)
{
	const char	*old;
	char		*new;
	int			shlvl;

	old = get_env_value(env, "SHLVL");
	if (old == NULL)
		shlvl = 1;
	else
	{
		shlvl = ft_atoi(old);
		shlvl += 1;
	}
	new = ft_itoa(shlvl);
	update_env(env, "SHLVL", new, stru);
	free(new);
}

char	*catch_line(char *name, char *value)
{
	char		*line;
	const char	*val;
	size_t		name_len;
	size_t		val_len;

	if (!name || !*name)
		return (NULL);
	if (!value)
		val = "";
	else
		val = value;
	name_len = ft_strlen(name);
	val_len = ft_strlen(val);
	line = malloc((name_len + 1) + (val_len + 1));
	if (!line)
		return (NULL);
	ft_memcpy(line, name, name_len);
	line[name_len] = '=';
	ft_memcpy(line + name_len + 1, val, val_len);
	line[name_len + 1 + val_len] = '\0';
	return (line);
}

char	**env_list_to_envp(t_env *env)
{
	t_tab	tab;

	init_tab(&tab, env);
	tab.envp = ft_calloc(tab.n_nodes + 1, sizeof(char *));
	if (!tab.envp)
		return (NULL);
	while (tab.node)
	{
		tab.line = catch_line(tab.node->name, tab.node->value);
		if (!tab.line)
		{
			free_doublechar(tab.envp);
			return (NULL);
		}
		tab.envp[tab.i] = tab.line;
		tab.i++;
		tab.node = tab.node->next;
	}
	tab.envp[tab.i] = NULL;
	return (tab.envp);
}
