/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_dup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:23:41 by skuor             #+#    #+#             */
/*   Updated: 2025/05/06 11:31:25 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_array_dup(char **array)
{
	char	**dup;
	int		i;

	if (!array)
		return (NULL);
	i = 0;
	while (array[i])
		i++;
	dup = ft_calloc(sizeof(char *), (i + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (array[i])
	{
		dup[i] = ft_strdup(array[i]);
		if (!dup[i])
			return (NULL);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}
