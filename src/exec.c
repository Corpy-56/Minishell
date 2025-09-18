/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarah <sarah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:33:30 by skuor             #+#    #+#             */
/*   Updated: 2025/09/18 13:44:50 by sarah            ###   ########.fr       */
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

/* void	run_two(t_cmd *cmd_a, t_cmd *cmd_b, t_shell *sh, char **env)
{
	int	pipefd[2];
	int	pid1;
	int	pid2;
	int	status1;
	int	status2;

	pipe(pipefd);
	if (pipe(pipefd) == -1)
		exit(1);
	pid1 = fork();
	if (pid1 == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			exit(1);
		close(pipefd[0]);
		close(pipefd[1]);
		if (is_builtin(cmd_a))
			exit(ft_test_bultins(cmd_a, sh));
		else
		{
			exec_external(cmd_a, sh, env);
			exit(127);
		}
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
			exit(1);
		close(pipefd[1]);
		close(pipefd[0]);
		if (is_builtin(cmd_b))
			exit(ft_test_bultins(cmd_b, sh));
		else
		{
			exec_external(cmd_b, sh, env);
			exit(127);
		}
	}
	close(pipefd[0]);
	close(pipefd[1]);
	status1 = waitpid(pid1, 0, 0);
	status2 = waitpid(pid2, 0, 0);
	sh->last_status = extract_exit_status(status2);
} */


void	run_pipes(t_cmd *head, t_shell *sh, char **env)
{
	int	fd[2];
	pid_t	*pids;
	pid_t	pid;
	int	i;
	int	n;
	int	prev_read;
	int	status;
	int	last_pid;
	t_cmd	**cmds;

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
			if (is_builtin(cmds[i]))
				exit(ft_test_bultins(cmds[i], sh));
			else
			{
				exec_external(cmds[i], sh, env);
				exit(127);
			}
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
	// while (i < n)
	// {
	// 	status = 0;
	// 	last_pid = 0;
	// 	waitpid(pids[i], &status, 0);
	// 	if (i == (n - 1))
	// 			last_pid = extract_exit_status(last_pid);
	// }
	sh->last_status = last_pid;
}

void	exec_cmd_line(t_shell *stru, char **env)
{
	t_cmd	*head;
	char	*path_val;
	int		n;

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
	head = stru->commande;
	n = count_maillons(head);
	if (n == 0)
		return ;
	if (n == 1)
	{
		if (is_builtin(head))
		{
			stru->last_status = ft_test_bultins(head, stru);
			if (stru->should_exit)
				return ;
		}
		else
			run_external(head, stru, env);
		return ;
	}
	if (n >= 2)
	{
		// run_two(head, head->next, stru, env);
		run_pipes(head, stru, env);
		return ;
	}
}
