/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 14:50:57 by skuor             #+#    #+#             */
/*   Updated: 2025/09/30 15:25:48 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env **env)
{
	t_env	*current;
	t_env	*next;

	if (!env || !*env)
		return ;
	current = *env;
	while (current)
	{
		next = current->next;
		free(current->name);
		free(current->value);
		if (current->path)
			free_doublechar(current->path);
		free(current->str);
		free(current);
		current = next;
	}
	if (env)
		*env = NULL;
}

void	free_tokens(t_tokens *token)
{
	t_tokens	*next;

	while (token)
	{
		next = token->next;
		free(token->str);
		free_doublechar(token->args);
		free(token);
		token = next;
	}
}

void	free_cmds(t_cmd *cmd)
{
	t_cmd	*next;

	while (cmd)
	{
		next = cmd->next;
		free_doublechar(cmd->args);
		free(cmd->cmd);
		free(cmd);
		cmd = next;
	}
}

void	free_doublechar(char **to_free)
{
	int	i;

	i = 0;
	if (to_free == NULL)
		return ;
	while (to_free[i])
	{
		free(to_free[i]);
		i++;
	}
	free(to_free);
}

void	free_fields(char **fields, size_t i)
{
	size_t	j;

	j = 0;
	while (j < i)
	{
		free(fields[j]);
		j++;
	}
	free(fields);
}
