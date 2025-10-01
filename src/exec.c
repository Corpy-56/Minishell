/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:33:30 by skuor             #+#    #+#             */
/*   Updated: 2025/10/01 14:57:01 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_maillons(t_cmd *cmd)
{
	int	n;

	n = 0;
	while (cmd)
	{
		n++;
		cmd = cmd->next;
	}
	return (n);
}

t_cmd	**collect_maillons(t_cmd *head, int n)
{
	t_cmd	**cmds;
	int		i;

	cmds = malloc(sizeof(t_cmd *) * (n + 1));
	if (!cmds)
		return (NULL);
	i = 0;
	while (head)
	{
		cmds[i] = head;
		head = head->next;
		i++;
	}
	cmds[i] = NULL;
	return (cmds);
}

void	run_pipes(t_cmd *head, t_shell *sh, char **env)
{
	int		fd[2];
	pid_t	*pids;
	pid_t	pid;
	int		i;
	int		n;
	int		prev_read;
	int		status;
	int		last_pid;
	t_cmd	**cmds;
//	int fd_test;
	
//	auto int fd_stdin = dup(0), fd_stdout;
//	fd_stdout = dup(1);
	//fd_test = 0;
	n = count_maillons(head);
	prev_read = -1;
	cmds = collect_maillons(head, n);
	pids = malloc(sizeof(pid_t) * n);
	if (!cmds || !pids)
		return ;
	i = 0;
	while (i < n)
	{
		if (i < (n - 1))
		{
			if (pipe(fd) == -1)
				exit(1);
		}
		pid = fork();
		if (pid == 0)
		{
			
			if (prev_read != -1)
			{
				if (dup2(prev_read, STDIN_FILENO) == -1)
					exit(1);
				close(prev_read);
			}
			if (i < (n - 1))
			{
				if (dup2(fd[1], STDOUT_FILENO) == -1)
					exit(1);
				close(fd[0]);
				close(fd[1]);
			}
			//je peux mettre les heredocs + redirections
			//fd_test = ft_first_ft_redirections(head, fd_test, sh);
			if (is_builtin(cmds[i]))
				exit(ft_test_bultins(cmds[i], sh));
			else
			{
				exec_external(cmds[i], sh, env);
			//	ft_close_fd(head, fd_stdin, fd_stdout, fd_test);
				exit(127);
			}
			//ft_close_fd(head, fd_stdin, fd_stdout, fd_test);
		}
		pids[i] = pid;
		if (prev_read != -1)
			close(prev_read);
		if (i < (n - 1))
		{
			close(fd[1]);
			prev_read = fd[0];
		}
		else
			prev_read = -1;
		status = 0;
		last_pid = 0;
		waitpid(pids[i], &status, 0);
		if (i == (n - 1))
			last_pid = extract_exit_status(last_pid);
		i++;
	}
	if (prev_read != -1)
		close(prev_read);
	sh->last_status = last_pid;
}

static void	reconstruct_path_dirs(t_shell *stru)
{
	char	*path_val;

	path_val = NULL;
	if (!stru->path_dirs)
	{
		if (stru->path_node && stru->path_node->value)
			path_val = stru->path_node->value;
		else
			path_val = get_env_value(stru->environ, "PATH");
		if (path_val)
			stru->path_dirs = ft_split(path_val, ':');
	}
}

void	exec_cmd_line(t_shell *stru, char **env)
{
	t_cmd	*head;

	auto int n, fd_stdin = dup(0), fd_stdout, fd = 0;
	fd_stdout = dup(1);
	reconstruct_path_dirs(stru);
	head = stru->commande;
	n = count_maillons(head);
	if (n == 0)
		return ;
	if (n == 1)
	{
		fd = ft_first_ft_redirections(head, fd, stru);
		if (is_builtin(head))
		{
			(void)ft_test_bultins(head, stru);
			if (stru->should_exit)
				return ;
		}
		else
			run_external(head, stru, env, fd);
		ft_close_fd(head, fd_stdin, fd_stdout, fd);
	}
	if (n >= 2)
		run_pipes(head, stru, env);
	return ;
}
