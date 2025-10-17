/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:39:18 by agouin            #+#    #+#             */
/*   Updated: 2025/10/17 15:10:21 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_heredoc(t_cmd *commande, int pidfd, int i, char *line)
{
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			return (-1);
		if (line[ft_strlen(line)] == '\0')
		{
			if (ft_strcmp(line, commande->heredoc[i]) == 0)
			{
				if (line != NULL)
					free(line);
				if (commande->heredoc[++i] == NULL)
					break ;
				continue ;
			}
			write(pidfd, line, ft_strlen(line));
			write(pidfd, "\n", 1);
		}
		if (line != NULL)
			free(line);
	}
	return (0);
}

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	t_shell	*shell;

	shell = NULL;
	(void)signum;
	(void)info;
	(void)context;
	shell = static_struct(shell);
	clean_heredoc(shell);
	if (shell->fd >= 0)
		close(shell->fd);
	if (shell->dup_0 >= 0)
		close(shell->dup_0);
	exit(130);
}

void	ft_child_heredoc(t_cmd *commande, t_shell *stru, int j, int i)
{
	struct sigaction	signale;
	t_cmd				*temp;

	temp = commande;
	while (temp->heredoc[i] != NULL)
		i++;
	i--;
	if (stru->fd == -1)
		exit (0);
	signal(SIGQUIT, SIG_IGN);
	signale.sa_sigaction = signal_handler;
	sigemptyset(&signale.sa_mask);
	signale.sa_flags = 0;
	sigaction(SIGINT, &signale, NULL);
	j = ft_heredoc(commande, stru->fd, 0, NULL);
	if (j == -1)
		printf("warning: here-document delimited by end-of-file (wanted `%s')\n",
			temp->heredoc[i]);
	clean_heredoc(stru);
	if (stru->fd >= 0)
		close(stru->fd);
	if (stru->dup_0 >= 0)
		close (stru->dup_0);
	exit (0);
}

int	parent_heredoc(pid_t pid, struct sigaction old_s, int fds, t_shell *sh)
{
	int					exit_code;
	int					status;

	waitpid(pid, &status, 0);
	sigaction(SIGINT, &old_s, NULL);
	if (sh->fd >= 0)
		close(sh->fd);
	exit_code = WEXITSTATUS(status);
	if ((WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		|| (WIFEXITED(status) && exit_code == 130))
	{
		unlink(".files");
		sh->last_status = 130;
		write(1, "\n", 1);
		return (-1);
	}
	if (WIFEXITED(status) && exit_code == 0)
	{
		fds = open(".files", O_RDONLY);
		unlink(".files");
		return (fds);
	}
	unlink(".files");
	sh->last_status = 1;
	return (-1);
}

int	ft_setup_heredoc(t_cmd *commande, t_shell *stru)
{
	pid_t				pid;
	int					fd;
	struct sigaction	new_signale;
	struct sigaction	old_signale;

	fd = 0;
	sigemptyset(&new_signale.sa_mask);
	new_signale.sa_handler = SIG_IGN;
	new_signale.sa_flags = 0;
	sigaction(SIGINT, &new_signale, &old_signale);
	stru->fd = open(".files", O_CREAT | O_RDWR | O_TRUNC, 0600);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		ft_child_heredoc(commande, stru, 0, 0);
	else if (pid > 0)
	{
		fd = parent_heredoc(pid, old_signale, 0, stru);
		if (fd == -1)
			stru->last_status = 130;
	}
	return (fd);
}