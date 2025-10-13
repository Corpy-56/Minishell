/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_exect_redirections.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:33:30 by skuor             #+#    #+#             */
/*   Updated: 2025/10/13 18:05:35 by skuor            ###   ########.fr       */
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

char *ft_free_str(char *str)
{
	free(str);
	return (NULL);
}

//static int	expand_exit_status(t_shell *stru, char **str)
//{
//	char	*status_str;

//	status_str = ft_itoa(stru->last_status);
//	append_str(str, status_str);
//	free(status_str);
//	return (2);
//}

char	*ft_expand_heredoc2(char *l, t_shell *sh, size_t i, size_t start)
{
	char *str;
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
			//if (i + 1 < len_str && l[i + 1] == '?')
			//	i += expand_exit_status(sh, &str);
			//else
			//	i = expand_var2(sh, l, i + 1, &str);
			i = expand_var2(sh, l, i + 1, &str);
			start = i;
		}
		else
			i++;
	}
	return (ft_end_expand(start, str, l, i));
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
		temp = ft_expand_heredoc2(line, stru, 0, 0);
		write(new_fd, temp, ft_strlen(line));
		if (ft_strcmp(temp, line) != 0)
			write(new_fd, "\n", 1);
		free(temp);
		free(line);
	}
	return (-1);
}

// int	ft_first_ft_redirections(t_cmd *head, int fd, t_shell *stru)
// {
// 	if (head->heredoc != NULL && (fd == -2 || fd == 0))
// 	{
// 		fd = ft_setup_heredoc(head, stru);
// 		if (fd == -1)
// 			return (fd);
// 		fd = ft_expand_heredoc(fd, stru);
// 	}
// 	if (head->fd_out_put1 != -2 && head->here == -2 )
// 	{
// 		dup2(head->fd_out_put1, STDOUT_FILENO);
// 		close(head->fd_out_put1);
// 	}
// 	if (head->fd_out_put2 != -2 && head->here == -2)
// 	{
// 		dup2(head->fd_out_put2, STDOUT_FILENO);
// 		close(head->fd_out_put2);
// 	}
// 	if (head->fd_int_put != -2)
// 	{
// 		dup2(head->fd_int_put, STDIN_FILENO);
// 		close(head->fd_int_put);
// 	}
// 	return (fd);
// }

int	ft_first_ft_redirections(t_cmd *head, int fd, t_shell *stru)
{
	if (head->heredoc != NULL && (fd == -2 || fd == 0))
	{
		fd = ft_setup_heredoc(head, stru);
		if (fd == -1)
			return (-1);
		fd = ft_expand_heredoc(fd, stru);
		if (fd == -1)
			return (-1);
	}
	if (head->fd_out_put1 != -2 && head->here == -2 )
	{
		dup2(head->fd_out_put1, STDOUT_FILENO);
		close(head->fd_out_put1);
		head->fd_out_put1 = -2;
	}
	if (head->fd_out_put2 != -2 && head->here == -2)
	{
		dup2(head->fd_out_put2, STDOUT_FILENO);
		close(head->fd_out_put2);
		head->fd_out_put2 = -2;
	}
	if (head->fd_int_put != -2)
	{
		dup2(head->fd_int_put, STDIN_FILENO);
		close(head->fd_int_put);
		head->fd_int_put = -2;
	}
	return (fd);
}
// void ft_close_fd(t_cmd *head, int fd_stdin, int fd_stdout, int hd_fd)
// {
//     (void)head;

//     // Heredoc: toujours fermer dans le parent s'il existe
//     if (hd_fd >= 0)
//         close(hd_fd);

//     // Restaurer puis fermer les sauvegardes SI elles sont valides
//     if (fd_stdout >= 0) { dup2(fd_stdout, STDOUT_FILENO); close(fd_stdout); }
//     if (fd_stdin  >= 0) { dup2(fd_stdin,  STDIN_FILENO); close(fd_stdin);  }
// }

// void	ft_close_fd(t_cmd *head, int fd_stdin, int fd_stdout, int fd)
// {
// 	(void)head;

// 	if (fd >= 0)
// 		close(fd);
// 	if (fd_stdout >= 0)
// 	{
// 		dup2(fd_stdout, 1);
// 		close(fd_stdout);
// 	}
// 	if (fd_stdin >= 0)
// 	{
// 		dup2(fd_stdin, 0);
// 		close(fd_stdin);
// 	}
// }

void	ft_close_fd(t_cmd *head, int fd_stdin, int fd_stdout, int fd)
{
	if (head->heredoc != NULL && isatty(fd) == 1)
	{
		//dup2(fd_stdin, 0);
		close(fd);
	}
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

void apply_cmd_redirs_in_child(t_cmd *cmd)
{
	if (cmd->here)
	{
		dup2(cmd->here, 0);
		close(cmd->here);
		cmd->here = -1;
	}
	if (cmd->fd_int_put >= 0)
	{
		dup2(cmd->fd_int_put, 0);
		close(cmd->fd_int_put);
		cmd->fd_int_put = -1;
	}
	if (cmd->fd_out_put1 >= 0)
	{
		dup2(cmd->fd_out_put1, 1);
		close(cmd->fd_out_put1);
		cmd->fd_out_put1 = -1;
	}
	if (cmd->fd_out_put2 >= 0)
	{
		dup2(cmd->fd_out_put2, 1);
		close(cmd->fd_out_put2);
		cmd->fd_out_put2 = -1;
	}
}
