/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:52:31 by agouin            #+#    #+#             */
/*   Updated: 2025/09/29 15:48:58 by skuor            ###   ########.fr       */
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
	if (ft_strncmp(new->name, "PATH", 4) == 0 && new->value != NULL)
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

char	*build_line(char *name, char *value)
{
	char	*line;
	size_t	name_len;
	size_t	val_len;

	name_len = ft_strlen(name);
	val_len = ft_strlen(value);
	if (!name || !*name)
		return (NULL);
	if (!value)
	{
		line = ft_strdup(name);
		return (line);
	}
	line = malloc((name_len + 1) + (val_len + 1));
	if (!line)
	{
		free(line);
		return (NULL);
	}
	ft_memcpy(line, name, name_len);
	line[name_len] = '=';
	ft_memcpy((line + name_len + 1), value, val_len);
	line[name_len + 1 + val_len] = '\0';
	return (line);
}

int	update_env(t_env *head, char *name, char *value, t_shell *stru)
{
	t_env	*node;
	t_env	*new_node;
	t_env	*last;
	char	*line;

	if (!head || !name || ft_strcmp(name, "") == 0)
		return (-1);
	node = find_var(head, name);
	if (node)
	{
		update_value(node, value);
		if (name && ft_strcmp(name, "PATH") == 0)
		{
			if (node->path)
				free_doublechar(node->path);
			if (node->value)
				node->path = ft_split(node->value, ':');
			else
				node->path = NULL;
			if (stru)
			{
				stru->path_node = node;
				if (stru->path_dirs)
					free_doublechar(stru->path_dirs);
				if (node->value)
					stru->path_dirs = ft_split(node->value, ':');
				else
					stru->path_dirs = NULL;
			}
		}
		return (0);
	}
	line = build_line(name, value);
	if (!line)
		return (-1);
	new_node = create_env_node(line);
	free(line);
	if (!new_node)
		return (-1);
	if (!head)
		head = new_node;
	else
	{
		last = head;
		while (last->next)
			last = last->next;
		last->next = new_node;
	}
	if (ft_strcmp(name, "PATH") == 0 && stru != NULL)
	{
		stru->path_node = new_node;
		if (stru->path_dirs)
			free_doublechar(stru->path_dirs);
		if (new_node->value)
			stru->path_dirs = ft_split(new_node->value, ':');
		else
			stru->path_dirs = NULL;
	}
	return (0);
}
