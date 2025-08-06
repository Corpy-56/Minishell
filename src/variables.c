/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 17:27:24 by skuor             #+#    #+#             */
/*   Updated: 2025/08/06 13:54:30 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	expand_var(t_tokens *token, int exit_status)
{
	char		*new_str;
	//t_tokens	new_token;
	size_t			i;
	char		*exit_str;

	new_str = ft_strdup("");
	i = 0;
	while (i < ft_strlen(token->str))
	{
		if (token->str[i] == '$')
		{
			i++;
			if (token->str[i] == '?')
			{
				exit_str = ft_itoa(exit_status);
				ft_strjoin(new_str, exit_str);
				free(exit_str);
				i++;
			}
			else if (check_valid_var(token->str))
			{
				
			}
		}	
		i++;
	
	}
	return (*token);
}

