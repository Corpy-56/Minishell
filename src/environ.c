/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:52:31 by agouin            #+#    #+#             */
/*   Updated: 2025/07/11 11:48:34 by agouin           ###   ########.fr       */
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
		environ = malloc(sizeof(t_env));
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