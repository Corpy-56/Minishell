/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:21:04 by skuor             #+#    #+#             */
/*   Updated: 2025/08/20 12:22:27 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error(int i, char *str, char *str2)
{
	(void)i;
	//i = 0;
	if (str2 != NULL)
		write(2, str2, (ft_strlen(str)));
	write(2, str, (ft_strlen(str)));
	return (-1);
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
	t_tokens	*next;

	while (token)
	{
		free(token->str);
		next = token->next;
		free(token);
		token = next;
	}
}

/* bool	is_local_var(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (false);
	while (str[i])
	{
		if (str[i] == '=')
			return (true);
		i++;
	}
	return (false);
} */

bool	is_local_var(char *s)
{
	int	i;

	if (!s || !s[0])
		return (false);
	if (!(isalpha(s[0]) || s[0] == '_'))
		return (false);
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (!(isalnum((unsigned char)s[i]) || s[i] == '_'))
			return (false);
		i++;
	}
	return (s[i] == '=');
}

void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		free(env);
		i++;
	}
	free(env);
}
