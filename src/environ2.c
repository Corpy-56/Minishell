/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:52:31 by agouin            #+#    #+#             */
/*   Updated: 2025/09/30 13:56:11 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*build_line(char *name, char *value)
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

static void	update_env2(t_env *node, char *name, t_shell *stru)
{
	if (!name || ft_strcmp(name, "") == 0)
		return ;
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

static void	update_env3(t_env *head, t_env *new_node, char *name, t_shell *stru)
{
	t_env	*last;

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
}

int	update_env(t_env *head, char *name, char *value, t_shell *stru)
{
	char	*line;
	t_env	*node;
	t_env	*new_node;

	if (!head || !name || ft_strcmp(name, "") == 0)
		return (-1);
	node = find_var(head, name);
	if (node)
	{
		update_value(node, value);
		if (name && ft_strcmp(name, "PATH") == 0)
			update_env2(node, name, stru);
		return (0);
	}
	line = build_line(name, value);
	if (!line)
		return (-1);
	new_node = create_env_node(line);
	free(line);
	if (!new_node)
		return (-1);
	update_env3(head, new_node, name, stru);
	return (0);
}
