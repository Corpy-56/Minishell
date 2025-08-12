/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 11:07:01 by skuor             #+#    #+#             */
/*   Updated: 2025/08/11 15:35:19 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_duplicate_env(char **env)
{
	int	i;

	auto t_env * fin = NULL, *a_debut = NULL, *environ = NULL;
	i = 0;
	while (env[i])
	{
		environ = ft_calloc(1, sizeof(t_env));
		if (environ == NULL)
			return (NULL);
		environ->i = i;
		environ->str = ft_strdup(env[i]);
		environ->next = NULL;
		if (a_debut == NULL)
		{
			a_debut = environ;
			fin = environ;
		}
		else
		{
			fin->next = environ;
			fin = environ;
		}
		i++;
	}
	return (a_debut);
}

int	ft_env(t_shell *stru)
{
	t_shell	*env_temp;

	env_temp = stru;
	while (env_temp->environ != NULL)
	{
		printf("%s\n", env_temp->environ->str);
		env_temp->environ = env_temp->environ->next;
	}
	return (0);
}

