/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:39:18 by agouin            #+#    #+#             */
/*   Updated: 2025/10/10 17:32:16 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_heredoc(t_cmd *commande, int pidfd, int i)
{
	char	*line;
	size_t	len_hd;

	while (1)
	{
		if (pidfd == -1)
			pidfd = open(".files", O_CREAT | O_RDWR | O_TRUNC, 0600);
		write(1, "> ", 2);
		line = get_next_line(0);
		if (line == NULL)
			return (-1);
		len_hd = ft_strlen(commande->heredoc[i]);
		if ((ft_strncmp(line, commande->heredoc[i], len_hd) == 0)
			&& (line[len_hd] == '\0' || line[len_hd] == '\n'))
		{
			free(line);
			close(pidfd);
			pidfd = -1;
			if (commande->heredoc[++i] == NULL)
				break ;
		}
		write(pidfd, line, ft_strlen(line));
		free(line);
	}
	return (0);
}

// void	signal_handler(int signum, siginfo_t *info, void *context)
// {
// 	(void)signum;
// 	(void)info;
// 	(void)context;
// 	write(1, "\n", 1);
// //	close(0);// comme ca je peux free tout avant de tout reafficher 
// 	exit(130);
// }

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		close(0);
	}
}

// void	ft_child_heredoc(t_cmd *commande, t_shell *stru)
// {
// 	struct sigaction	signale;
// 	int					pidfd;
// 	t_cmd				*temp;
// 	int					i;
// 	int					j;

// 	j = 0;
// 	i = 0;
// 	pidfd = -1;
// 	temp = commande;
// 	while (temp->heredoc[i] != NULL)
// 		i++;
// 	i--;
// 	signale.sa_sigaction = signal_handler;
// 	sigemptyset(&signale.sa_mask);
// 	signale.sa_flags = SA_SIGINFO;
// 	sigaction(SIGINT, &signale, NULL);
// 	j = ft_heredoc(commande, pidfd, 0);
// 	if (j == -1)
// 		printf("\nwarning: here-document delimited by end-of-file (wanted `%s')\n", temp->heredoc[i]);
// 	clean_heredoc(stru);
// 	if (isatty(pidfd) == 1)
// 		close (pidfd);
// 	exit (0);
// }

void	ft_child_heredoc(t_cmd *commande, t_shell *stru)
{
	struct sigaction	signale;
	int					pidfd;
	t_cmd				*temp;
	int					i;
	int					j;
	int					status;

	j = 0;
	i = 0;
	pidfd = -1;
	temp = commande;
	while (temp->heredoc[i] != NULL)
		i++;
	i--;
	signale.sa_sigaction = signal_handler;
	sigemptyset(&signale.sa_mask);
	signale.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &signale, NULL);
	j = ft_heredoc(commande, pidfd, 0);
	if (j == -1)
	{
		printf("\nwarning: here-document delimited by end-of-file (wanted `%s')\n", temp->heredoc[i]);
		status = 130;
	}
	else
		status = 0;
	clean_heredoc(stru);
	if (isatty(pidfd) == 1)
		close (pidfd);
	_exit (status);
}

int	parent_heredoc(pid_t pid, struct sigaction old_s, int fd)
{
	int					exit_code;
	int					status;

	waitpid(pid, &status, 0);
	sigaction(SIGINT, &old_s, NULL);
	exit_code = WEXITSTATUS(status);
	if (exit_code == 130)
		return (-1);
	fd = open(".files", O_RDONLY);
	unlink(".files");
	return (fd);
}

int	ft_setup_heredoc(t_cmd *commande, t_shell *stru)
{
	pid_t				pid;
	int					fd;
	struct sigaction	new_signale;
	struct sigaction	old_signale;

	sigemptyset(&new_signale.sa_mask);
	new_signale.sa_handler = SIG_IGN;
	new_signale.sa_flags = 0;
	sigaction(SIGINT, &new_signale, &old_signale);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		ft_child_heredoc(commande, stru);
	else if (pid > 0)
	{
		fd = parent_heredoc(pid, old_signale, 0);
		return (fd);
	}
	return (0);
}
