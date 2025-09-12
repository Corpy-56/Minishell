/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:52:31 by agouin            #+#    #+#             */
/*   Updated: 2025/09/12 12:21:36 by skuor            ###   ########.fr       */
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

/* t_env	*ft_duplicate_env(char **env)
{
	int	i;

	auto t_env * fin = NULL, *a_debut = NULL, *new;
	i = 0;
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
		i++;
	}
	return (a_debut);
} */

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
