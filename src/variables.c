/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:09:43 by skuor             #+#    #+#             */
/*   Updated: 2025/08/05 12:50:59 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	expand_variables(t_tokens *token, char exit_status)
{
	char	*new;
	int			i;

	new = malloc(sizeof(char));
	i = 0;
	while (i < ft_strlen(new))
	{
		if (token->str[i] == '$')
			i++;
		else if (check_valid_var(new->str[i]))
		{
			int	start = i +1;
			int end = start;
			
		}
		{
			
		}
		i++;
	}
}