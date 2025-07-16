/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:21:04 by skuor             #+#    #+#             */
/*   Updated: 2025/07/16 16:16:46 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error(int i, char *str)
{
	i = 0;
	i++;
	printf("%d", i);
	write(2, "Error\n", 7);
	write(2, &str, ft_strlen(str));
	//exit(EXIT_FAILURE);
	return (0);
}

int	white_space(char *str, int i)
{
	while (str[i] != '\0' && (str[i] == 32 || str[i] == 9))
		i++;
	if (str[i] != 32 && str[i] != 9 && str[i] != '\0')
		return (i);
	else if (str[i] == '\0')
		return (-1);
	return (0);
}

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args);
		i++;
	}
	free(args);
}

void	free_tokens(t_tokens *token)
{
	while (token)
	{
		free(token);
		token = token->next;
	}
	free(token);
}
