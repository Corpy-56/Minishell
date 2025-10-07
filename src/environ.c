/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:52:31 by agouin            #+#    #+#             */
/*   Updated: 2025/10/07 12:13:56 by skuor            ###   ########.fr       */
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
	if (ft_strncmp(new->name, "PATH", 5) == 0 && new->value != NULL)
		new->path = ft_split(new->value, ':');
	else
		new->path = NULL;
	new->next = NULL;
	return (new);
}

t_env	*ft_duplicate_env(char **env, t_shell *stru)
{
	int	i;

	auto t_env * fin = NULL, *a_debut = NULL, *new;
	i = 0;
	stru->path_node = NULL;
	stru->path_dirs = NULL;
	while (env[i])
	{
		new = create_env_node(env[i]);
		if (!new)
			return (NULL);
		if (a_debut == NULL)
			a_debut = new;
		else
			fin->next = new;
		fin = new;
		if (stru->path_node == NULL
			&& ft_strncmp(new->name, "PATH", 5) == 0 && new->value != NULL )
		{
			stru->path_node = new;
			stru->path_dirs = ft_split(new->value, ':');
		}
		i++;
	}
	return (a_debut);
}

void	update_shlvl(t_env *env, t_shell *stru)
{
	char	*old;
	char	*new;
	int		shlvl;

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
	char	**envp;
	char	*line;
	int		n_nodes;
	size_t	i;
	t_env	*node;

	i = 0;
	node = env;
	n_nodes = count_nodes(env);
	envp = ft_calloc(n_nodes + 1, sizeof(char *));
	if (!envp)
		return (NULL);
	while (node)
	{
		line = catch_line(node->name, node->value);
		if (!line)
		{
			free_doublechar(envp);
			return (NULL);
		}
		envp[i] = line;
		i++;
		node = node->next;
	}
	envp[i] = NULL;
	return (envp);
}
