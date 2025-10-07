/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:39:18 by agouin            #+#    #+#             */
/*   Updated: 2025/10/06 18:26:50 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_heredoc(t_cmd *commande, int pidfd, int i)
{
	char	*line;

	while (1)
	{
		if (pidfd == -1)
			pidfd = open(".files", O_CREAT | O_RDWR | O_TRUNC, 0600);
		write(1, "> ", 2);
		line = get_next_line(0);
		if (line == NULL)
			return (-1);
		if (ft_strncmp(line, commande->heredoc[i],
				ft_strlen(commande->heredoc[i])) == 0)
		{
			close(pidfd);
			pidfd = -1;
			if (commande->heredoc[++i] == NULL)
			{
				free(line);
				break ;
			}
		}
		write(pidfd, line, ft_strlen(line));
	}
	return (0);
}

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	(void)signum;
	(void)info;
	(void)context;
	write(1, "\n", 1);
//	close(0);// comme ca je peux free tout avant de tout reafficher 
	exit(130);
}

void	ft_child_heredoc(t_cmd *commande)
{
	struct sigaction	signale;
	int					pidfd;
	t_cmd				*temp;
	int i;
	int j;

	j = 0;
	i = 0;
	pidfd = -1;
	temp = commande;
	while(temp->heredoc[i] != NULL)
		i++;
	i--;
	signale.sa_sigaction = signal_handler;
	sigemptyset(&signale.sa_mask);
	signale.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &signale, NULL);
	j = ft_heredoc(commande, pidfd, 0);
	if (j == -1)
		printf("\nwarning: here-document delimited by end-of-file (wanted `%s')\n", temp->heredoc[i]);
	if (isatty(pidfd) == 1)
		close (pidfd);
	exit (0);
}

int	ft_setup_heredoc(t_cmd *commande)
{
	pid_t				pid;
	int					status;
	int					fd;
	struct sigaction	new_signale;
	struct sigaction	old_signale;

	sigemptyset(&new_signale.sa_mask);
	new_signale.sa_handler = SIG_IGN;
	new_signale.sa_flags = 0;
	sigaction(SIGINT, &new_signale, &old_signale);
	pid = fork();
	if (pid == -1)
		return (-1);// a revoir
	if (pid == 0)
		ft_child_heredoc(commande);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		sigaction(SIGINT, &old_signale, NULL);
		int exit_code = WEXITSTATUS(status);
   		if (exit_code == 130)
			return (-1);
		fd = open(".files", O_RDONLY);
		unlink(".files");
		return (fd);
	}
	return (0);
}
