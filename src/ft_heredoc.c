/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:39:18 by agouin            #+#    #+#             */
/*   Updated: 2025/10/14 16:35:44 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static struct termios orig_termios;
struct termios saved_term;
extern t_shell *g_shell;

// int	ft_heredoc(t_cmd *commande, int pidfd, int i)
// {
// 	char	*line;
// 	char	*temp;
// 	int		k;

// 	k = 0;
// 	temp = NULL;
// 	line = NULL;
// 	while (1)
// 	{
// 		if (pidfd == -1)
// 			pidfd = open(".files", O_CREAT | O_RDWR | O_TRUNC, 0600);
// 		if (k == 0)
// 			write(1, "> ", 2);
// 		line = get_next_line(0);
// 		if (line == NULL)
// 		{
// 			if (k == 0)
// 				return (-1);
// 			continue ;
// 			//if (temp && *temp)
// 			//{
// 			//	write(pidfd, temp, ft_strlen(temp));
// 			//	write(pidfd, "\n", 1);
// 			//	free(temp);
// 			//}
// 			//printf("A\n");
// 			//else
// 			//{
// 			//	write(2, "warning: here-document delimited by end-of-file (wanted `", 57);
// 			//	write(2, commande->heredoc[i], ft_strlen(commande->heredoc[i]));
// 			//	write(2, "`)\n", 3);
// 			//}
// 			//return (-1);
// 		}
// 		if ((line[ft_strlen(line) - 1] != '\n' && ft_strlen(line) > 0))
// 		{
// 			k = 1;
// 			//char *li;
			
// 			//li = ft_strjoin(temp, line);
// 			//free(temp);
// 			//temp = li;
// 			//free(line);
// 			//printf("%s", temp);
// 			continue ;
// 		}
// 		else
// 		{
// 		//	if (temp != NULL)
// 		//	{
// 		//		line = ft_strjoin(temp, line);
// 		//		free(temp);
// 		//	}
// 			//if (temp)
// 			//{
// 			//	char *joined = ft_strjoin(temp, line);
// 			//	free(temp);
// 			//	free(line);
// 			//	line = joined;
// 			//	temp = NULL;
// 			//}
// 			k = 0;
// 		}
// 		if (line[ft_strlen(line) - 1] == '\n')
// 		{
// 			if ((ft_strncmp(line, commande->heredoc[i],
// 					ft_strlen(commande->heredoc[i])) == 0) && (line[ft_strlen(commande->heredoc[i])] == '\0'
// 					|| line[ft_strlen(commande->heredoc[i])] == '\n'))
// 			{
// 				close(pidfd);
// 				pidfd = -1;
// 				if (commande->heredoc[++i] == NULL)
// 				{
// 					if (line != NULL)
// 						(free(line), line = NULL);
// 					break ;
// 				}
// 			}
// 			write(pidfd, line, ft_strlen(line));
// 			free(line);
// 			line = NULL;
// 		}
// 	}
// 	if (line)
// 		free(line);
// 	return (0);
// }

int	ft_heredoc(t_cmd *commande, int pidfd, int i)
{
	char	*line;
	char	*temp;
	char	*join;
	int		k;

	k = 0;
	join = NULL;
	temp = NULL;
	line = NULL;
	while (1)
	{
		if (pidfd == -1)
		{
			pidfd = open(".files", O_CREAT | O_RDWR | O_TRUNC, 0600);
			if (pidfd == -1)
				return (-1);
		}
		if (k == 0)
			write(1, "> ", 2);
		line = get_next_line(0);
		if (line == NULL)
		{
			if (k == 0)
			{
				if (pidfd == -1)
				{
					close(pidfd);
					pidfd = -1;
				}
				get_next_line(-1);
				return (-1);
			}
			continue ;
		}
		if (line != NULL && (line[ft_strlen(line) - 1] != '\n' && ft_strlen(line) > 0))
		{
			k = 1;
			if (temp == NULL)
				temp = ft_strdup(line);
			else
			{
				join = ft_strjoin(temp, line);
				temp = ft_strdup(join);
				free(join);
			}
			free(line);
			line = NULL;
			continue ;
		}
		else
			k = 0;
		if (line[ft_strlen(line) - 1] == '\n')
		{
			if (temp != NULL)
			{
				join = ft_strjoin(temp, line);
				free(temp);
				free(line);
				line = NULL;
				line = ft_strdup(join);
				free(join);
			}
			if ((ft_strncmp(line, commande->heredoc[i],
					ft_strlen(commande->heredoc[i])) == 0) && (line[ft_strlen(commande->heredoc[i])] == '\0'
					|| line[ft_strlen(commande->heredoc[i])] == '\n'))
			{
				// close(pidfd);
				// pidfd = -1;
				if (pidfd == -1)
				{
					close(pidfd);
					pidfd = -1;
				}
				free(line);
				get_next_line(-1);
				if (commande->heredoc[++i] == NULL)
					break ;
				continue ;
			}
			write(pidfd, line, ft_strlen(line));
			//free(line);

		}
		if (line != NULL)
			free(line);

	}
	if (pidfd == -1)
	{
		close(pidfd);
		pidfd = -1;
	}
	return (0);
}

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	int	j;

	(void)signum;
	(void)info;
	(void)context;
	j = access(".files", F_OK);
	if (j == 0)
		unlink(".files");
	write(1, "^C", 2);
	write(1, "\n", 1);
	close(0);// comme ca je peux free tout avant de tout reafficher 
	exit(130);
}


void disable_echoctl(void)
{
    struct termios term;

    if (tcgetattr(STDIN_FILENO, &term) == -1)
        return;
    orig_termios = term;
    term.c_lflag &= ~(ECHOCTL);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	ft_child_heredoc(t_cmd *commande, t_shell *stru)
{
	struct sigaction	signale;
	int					pidfd;
	t_cmd				*temp;
	int					i;
	int					j;

	j = 0;
	i = 0;
	pidfd = -1;
	temp = commande;
	while (temp->heredoc[i] != NULL)
		i++;
	i--;
	disable_echoctl();
	signal(SIGQUIT, SIG_IGN);
	signale.sa_sigaction = signal_handler;
	sigemptyset(&signale.sa_mask);
	signale.sa_flags = 0;
	sigaction(SIGINT, &signale, NULL);
	j = ft_heredoc(commande, pidfd, 0);
	if (j == -1)
		printf("\nwarning: here-document delimited by end-of-file (wanted `%s')\n", temp->heredoc[i]);
	clean_heredoc(stru);
	if (isatty(pidfd) == 1)
		close (pidfd);
	_exit (0);
}


void save_termios(void)
{
    tcgetattr(STDIN_FILENO, &saved_term);
}

void restore_termios(void)
{
    tcsetattr(STDIN_FILENO, TCSANOW, &saved_term);
}

// int	parent_heredoc(pid_t pid, struct sigaction old_s, int fd)
// {
// 	int					exit_code;
// 	int					status;

// 	waitpid(pid, &status, 0);
// 	restore_termios();
// 	sigaction(SIGINT, &old_s, NULL);
// 	exit_code = WEXITSTATUS(status);
// 	if (exit_code == 130)
// 		return (-1);
// 	else
// 	{
// 		fd = open(".files", O_RDONLY);
// 		unlink(".files");
// 	}
// 	return (fd);
// }

// int	parent_heredoc(pid_t pid, struct sigaction old_s, int fd, t_shell *sh)
// {
// 	int					exit_code;
// 	int					status;

// 	waitpid(pid, &status, 0);
// 	restore_termios();
// 	sigaction(SIGINT, &old_s, NULL);
// 	// if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
// 	// {
// 	// 	clean_heredoc(sh);
// 	// 	return (-1);
// 	// }
// 	exit_code = WEXITSTATUS(status);
// 	if (exit_code == 130)
// 	{
// 		// clean_heredoc(sh);
// 		sh->hdc_interrupted = 1;
// 		return (-1);
// 	}
// 	else
// 	{
// 		fd = open(".files", O_RDONLY);
// 		unlink(".files");
// 	}
// 	return (fd);
// }

int	parent_heredoc(pid_t pid, struct sigaction old_s, int fd, t_shell *sh)
{
	int					exit_code;
	int					status;

	waitpid(pid, &status, 0);
	restore_termios();
	sigaction(SIGINT, &old_s, NULL);

	exit_code = WEXITSTATUS(status);
	if ((WIFSIGNALED(status) && WTERMSIG(status) == SIGINT )|| (WIFEXITED(status) && exit_code == 130))
	{
		get_next_line(-1);
		unlink(".files");
		sh->last_status = 130;
		// sh->hdc_interrupted = 1;
		// clean_heredoc(sh);
		return (-1);
	}
	if (WIFEXITED(status) && exit_code == 0)
	{
		fd = open(".files", O_RDONLY);
		unlink(".files");
		return (fd);
	}
	unlink(".files");
	get_next_line(-1);
	sh->last_status = 1;
	return (-1);
}

// int	ft_setup_heredoc(t_cmd *commande, t_shell *stru)
// {
// 	pid_t				pid;
// 	int					fd;
// 	struct sigaction	new_signale;
// 	struct sigaction	old_signale;

// 	sigemptyset(&new_signale.sa_mask);
// 	new_signale.sa_handler = SIG_IGN;
// 	new_signale.sa_flags = 0;
// 	sigaction(SIGINT, &new_signale, &old_signale);
// 	save_termios();
// 	pid = fork();
// 	if (pid == -1)
// 		return (-1);
// 	if (pid == 0)
// 		ft_child_heredoc(commande, stru);
// 	else if (pid > 0)
// 	{
// 		fd = parent_heredoc(pid, old_signale, 0);
// 		return (fd);
// 	}
// 	return (0);
// }

int	ft_setup_heredoc(t_cmd *commande, t_shell *stru)
{
	pid_t				pid;
	int					fd = 0;
	struct sigaction	new_signale;
	struct sigaction	old_signale;

	sigemptyset(&new_signale.sa_mask);
	new_signale.sa_handler = SIG_IGN;
	new_signale.sa_flags = 0;
	sigaction(SIGINT, &new_signale, &old_signale);
	save_termios();
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		ft_child_heredoc(commande, stru);
	else if (pid > 0)
	{
		fd = parent_heredoc(pid, old_signale, 0, stru);
		if (fd == -1)
			stru->last_status = 130;
	}
	return (fd);
}
