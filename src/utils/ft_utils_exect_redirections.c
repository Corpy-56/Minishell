/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_exect_redirections.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:33:30 by skuor             #+#    #+#             */
/*   Updated: 2025/10/17 19:54:42 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_end_expand(size_t start, char *str, char *line, size_t i)
{
	size_t	j;

	j = start;
	while (j < i)
	{
		if (append_char(&str, line[j]) < 0)
		{
			free(str);
			return (NULL);
		}
		j++;
	}
	return (str);
}

char	*ft_expand_heredoc2(char *l, t_shell *sh, size_t i, size_t start)
{
	char	*str;
	size_t	j;
	size_t	len_str;

	len_str = ft_strlen(l);
	str = ft_calloc(1, 1);
	if (!str)
		return (NULL);
	while (i < len_str)
	{
		if (l[i] == '$')
		{
			j = start;
			while (j < i)
			{
				if (append_char(&str, l[j++]) < 0)
					return (ft_free_str(str));
			}
			i = expand_var2(sh, l, i + 1, &str);
			start = i;
		}
		else
			i++;
	}
	return (ft_end_expand(start, str, l, i));
}

int	ft_expand_heredoc(int fd, t_shell *stru, int new_fd)
{
	char	*line;
	char	*temp;

	new_fd = open(".files_expand", O_CREAT | O_RDWR | O_TRUNC, 0600);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			close_fds(&fd);
			close_fds(&new_fd);
			new_fd = open(".files_expand", O_CREAT | O_RDWR, 0600);
			unlink(".files_expand");
			return (new_fd);
		}
		temp = ft_expand_heredoc2(line, stru, 0, 0);
		write(new_fd, temp, ft_strlen(line));
		if (ft_strcmp(temp, line) != 0)
			write(new_fd, "\n", 1);
		free(temp);
		free(line);
	}
	(close_fds(&new_fd), unlink(".files_expand"));
	return (-1);
}

void	apply_cmd_redirs_in_child2(t_cmd *cmd)
{
	if (cmd->here >= 0)
	{
		dup2(cmd->here, 0);
		close_fds(&cmd->here);
		cmd->here = -1;
	}
}

void	apply_cmd_redirs_in_child(t_cmd *cmd, t_shell *shell)
{
	apply_cmd_redirs_in_child2(cmd);
	if (cmd->fd_int_put >= 0)
	{
		dup2(shell->dup_0, 0);
		close_fds(&cmd->fd_int_put);
		close(shell->dup_0);
		shell->dup_0 = -1;
		cmd->fd_int_put = -1;
	}
	if (cmd->fd_out_put1 >= 0)
	{
		dup2(shell->dup_1, 1);
		close_fds(&cmd->fd_out_put1);
		close(shell->dup_1);
		shell->dup_1 = -1;
		cmd->fd_out_put1 = -1;
	}
	if (cmd->fd_out_put2 >= 0)
	{
		dup2(shell->dup_1, 1);
		close_fds(&cmd->fd_out_put2);
		close(shell->dup_1);
		shell->dup_1 = -1;
		cmd->fd_out_put2 = -1;
	}
}
