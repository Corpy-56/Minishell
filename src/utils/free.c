/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 14:50:57 by skuor             #+#    #+#             */
/*   Updated: 2025/10/16 19:44:14 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	free_redirs(t_redir *redir)
{
	t_redir	*next;

	while (redir)
	{
		next = redir->next;
		free(redir->target);
		free(redir);
		redir = next;
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
		if (cmd->heredoc)
			free_doublechar(cmd->heredoc);
		if (cmd->redirs)
			free_redirs(cmd->redirs);
		close_fd(cmd);
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
