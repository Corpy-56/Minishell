/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:39:18 by agouin            #+#    #+#             */
/*   Updated: 2025/10/11 18:50:50 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static struct termios orig_termios;
struct termios saved_term;

volatile sig_atomic_t g_hd_abort = 0;


void	heredoc_sigint(int sig)
{
	(void)sig;
	g_hd_abort = 1;
	write(STDOUT_FILENO, "\n", 1);
	close(STDIN_FILENO);
}

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
		if (g_hd_abort)
		{
			if (line)
				free(line);
			if (temp)
				free(temp);
			if (isatty(pidfd) == 1)
				close (pidfd);
			return (-1);
		}
		if (pidfd == -1)
			pidfd = open(".files", O_CREAT | O_RDWR | O_TRUNC, 0600);
		if (k == 0)
			write(1, "> ", 2);
		line = get_next_line(0);
		if (line == NULL)
		{
			if (k == 0)
				return (-1);
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
				close(pidfd);
				pidfd = -1;
				free(line);
				if (commande->heredoc[++i] == NULL)
				{
					// if (line != NULL)
					// 	(free(line), line = NULL);
					break ;
				}
				continue ;
			}
			write(pidfd, line, ft_strlen(line));
			//free(line);
		}
		if (line != NULL)
			free(line);
	}
	// if (line)
	// 	free(line);
	return (0);
}

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	int	j;

	(void)signum;
	(void)info;
	(void)context;
	g_hd_abort = 1;
	j = access(".files", F_OK);
	if (j == 0)
		unlink(".files");
	write(1, "^C", 2);
	write(1, "\n", 1);
	// close(0);// comme ca je peux free tout avant de tout reafficher 
	_exit(130); // je pense que le probleme de still reachables vient de la mais je n'arrive tjs pas a le regler 
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
	signale.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &signale, NULL);
	j = ft_heredoc(commande, pidfd, 0);
	if (j == -1)
		printf("\nwarning: here-document delimited by end-of-file (wanted `%s')\n", temp->heredoc[i]);
	clean_heredoc(stru);
	if (isatty(pidfd) == 1)
		close (pidfd);
	if (g_hd_abort)
		_exit(130);
	else
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

int	parent_heredoc(pid_t pid, struct sigaction old_s, int fd, t_shell *sh)
{
	int		exit_code;
	int		status;
	(void)sh;

	waitpid(pid, &status, 0);
	restore_termios();
	sigaction(SIGINT, &old_s, NULL);
	exit_code = WEXITSTATUS(status);
	if (exit_code == 130)
	{
		clean_heredoc(sh);
		get_next_line(-1);
		return (-1);
	}
	else
	{
		fd = open(".files", O_RDONLY);
		unlink(".files");
	}
	return (fd);
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

//int	ft_heredoc(t_cmd *commande, int pidfd, int i)
//{
//	char	*line;

//	while (1)
//	{
//		if (pidfd == -1)
//			pidfd = open(".files", O_CREAT | O_RDWR | O_TRUNC, 0600);
//		write(1, "> ", 2);
//		line = get_next_line(0);
//		if (line == NULL)
//			return (-1);
//		if (ft_strncmp(line, commande->heredoc[i],
//				ft_strlen(commande->heredoc[i])) == 0)
//		{
//			close(pidfd);
//			pidfd = -1;
//			if (commande->heredoc[++i] == NULL)
//			{
//				free(line);
//				break ;
//			}
//		}
//		write(pidfd, line, ft_strlen(line));
//	}
//	return (0);
//}

//void	signal_handler(int signum, siginfo_t *info, void *context)
//{
//	(void)signum;
//	(void)info;
//	(void)context;
//	write(1, "\n", 1);
////	close(0);// comme ca je peux free tout avant de tout reafficher 
//	exit(130);
//}

//void	ft_child_heredoc(t_cmd *commande)
//{
//	struct sigaction	signale;
//	int					pidfd;
//	int i;
//	int j;

//	j = 0;
//	i = 0;
//	pidfd = -1;
//	signale.sa_sigaction = signal_handler;
//	sigemptyset(&signale.sa_mask);
//	signale.sa_flags = SA_SIGINFO;
//	sigaction(SIGINT, &signale, NULL);
//	j = ft_heredoc(commande, pidfd, i);
//	if (j == -1)
//		printf("\nwarning: here-document delimited by end-of-file (wanted `%s')\n", commande->heredoc[i]);
//	if (isatty(pidfd) == 1)
//		close (pidfd);
//	exit (0);
//}

//int	ft_setup_heredoc(t_cmd *commande)
//{
//	pid_t				pid;
//	int					status;
//	int					fd;
//	struct sigaction	new_signale;
//	struct sigaction	old_signale;

//	sigemptyset(&new_signale.sa_mask);
//	new_signale.sa_handler = SIG_IGN;
//	new_signale.sa_flags = 0;
//	sigaction(SIGINT, &new_signale, &old_signale);
//	pid = fork();
//	if (pid == -1)
//		return (-1);
//	if (pid == 0)
//		ft_child_heredoc(commande);
//	else if (pid > 0)
//	{
//		waitpid(pid, &status, 0);
//		sigaction(SIGINT, &old_signale, NULL);
//		int exit_code = WEXITSTATUS(status);
//   		if (exit_code == 130)
//			return (-1);
//		fd = open(".files", O_RDONLY);
//		unlink(".files");
//		return (fd);
//	}
//	return (0);
//}
