/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_exect_redirections.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:33:30 by skuor             #+#    #+#             */
/*   Updated: 2025/10/09 10:59:30 by skuor            ###   ########.fr       */
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

char	*ft_expand_heredoc2(char *line, t_shell *stru)
{
	auto char *str;
	auto size_t i = 0, start = 0, len_str = ft_strlen(line), j;
	str = ft_calloc(1, 1);
	if (!str)
		return (NULL);
	while (i < len_str)
	{
		if (line[i] == '$')
		{
			j = start;
			while (j < i)
			{
				if (append_char(&str, line[j++]) < 0)
				{
					free(str);
					return (NULL);
				}
			}
			i = expand_var2(stru, line, i + 1, &str);
			start = i;
		}
		else
			i++;
	}
	return (ft_end_expand(start, str, line, i));
}

int	ft_expand_heredoc(int fd, t_shell *stru)
{
	char	*line;
	int		new_fd;
	char	*temp;

	new_fd = open(".files_expand", O_CREAT | O_RDWR | O_TRUNC, 0600);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			close(fd);
			close(new_fd);
			new_fd = open(".files_expand", O_CREAT | O_RDWR, 0600);
			unlink(".files_expand");
			return (new_fd);
		}
		temp = ft_expand_heredoc2(line, stru);
		write(new_fd, temp, ft_strlen(line));
		if (ft_strcmp(temp, line) != 0)
			write(new_fd, "\n", 1);
		free(temp);
		free(line);
	}
	return (-1);
}

int	ft_first_ft_redirections(t_cmd *head, int fd, t_shell *stru)
{
	if (head->heredoc != NULL && (fd == -2 || fd == 0))
	{
		fd = ft_setup_heredoc(head);
		if (fd == -1)
			return (fd);
		fd = ft_expand_heredoc(fd, stru);
	}
	if (head->fd_out_put1 != -2 && head->here == -2)
	{
		dup2(head->fd_out_put1, STDOUT_FILENO);
		close(head->fd_out_put1);
	}
	if (head->fd_out_put2 != -2 && head->here == -2)
	{
		dup2(head->fd_out_put2, STDOUT_FILENO);
		close(head->fd_out_put2);
	}
	if (head->fd_int_put != -2)
	{
		dup2(head->fd_int_put, STDIN_FILENO);
		close(head->fd_int_put);
	}
	return (fd);
}

void	ft_close_fd(t_cmd *head, int fd_stdin, int fd_stdout, int fd)
{
	if (head->heredoc != NULL && isatty(fd) == 1)
		close(fd);
	if (head->fd_out_put1 != -2 || head->fd_out_put2 != -2)
	{
		dup2(fd_stdout, 1);
		close(fd_stdout);
	}
	if (head->fd_int_put != -2)
	{
		dup2(fd_stdin, 0);
		close(fd_stdin);
	}
}
