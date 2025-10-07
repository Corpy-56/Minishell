/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:33:30 by skuor             #+#    #+#             */
/*   Updated: 2025/10/07 17:23:46 by skuor            ###   ########.fr       */
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

t_cmd	**ft_test_heredoc_pipes(int i, int n, t_cmd **cmds, t_shell *sh)
{
	while (i < n)
	{
		if (cmds[i]->heredoc != NULL)
		{
			cmds[i]->here = ft_setup_heredoc(cmds[i]);
			if (cmds[i]->here == -1)
				return (cmds);
			cmds[i]->here = ft_expand_heredoc(cmds[i]->here, sh);
		}
		i++;
	}
	return (cmds);
}

void	ft_first_ft_redirections2(t_cmd *head)
{
	if (head->fd_out_put1 != -2)
	{
		dup2(head->fd_out_put1, STDOUT_FILENO);
		close(head->fd_out_put1);
	}
	if (head->fd_out_put2 != -2)
	{
		dup2(head->fd_out_put2, STDOUT_FILENO);
		close(head->fd_out_put2);
	}
	if (head->fd_int_put != -2)
	{
		dup2(head->fd_int_put, STDIN_FILENO);
		close(head->fd_int_put);
	}
}

// void	run_pipes(t_cmd *head, t_shell *sh)
// {
// 	int		fd[2];
// 	pid_t	*pids;
// 	pid_t	pid;
// 	int		i;
// 	int		n;
// 	int		prev_read;
// 	int		status;
// 	int		last_pid;
// 	int		builtins;
// 	t_cmd	**cmds;

// 	n = count_maillons(head);
// 	prev_read = -1;
// 	cmds = collect_maillons(head, n);
// 	pids = malloc(sizeof(pid_t) * n);
// 	if (!pids || !cmds)
// 	{
// 		free(pids);
// 		free(cmds);
// 		return ;
// 	}
// 	i = 0;
// 	while (i < n)
// 	{
// 		if (i < (n - 1))
// 		{
// 			if (pipe(fd) == -1)
// 			{
// 				if (prev_read != -1)
// 					close (prev_read);
// 				free(pids);
// 				free(cmds);
// 				exit(1);
// 			}
// 		}
// 		pid = fork();
// 		if (pid == -1)
// 		{
// 			if (i < n - 1)
// 			{
// 				close(fd[0]);
// 				close(fd[1]);
// 			}
// 			if (prev_read != -1)
// 				close(prev_read);
// 			free(pids);
// 			free(cmds);
// 			exit (1);
// 		}
// 		if (pid == 0)
// 		{
// 			if (cmds[i]->here != -2)
// 			{
// 				if (dup2(cmds[i]->here, STDIN_FILENO) == -1)
// 					exit(1);
// 				if (i == 0 || cmds[i]->fd_int_put != -2)
// 					close(cmds[i]->here);
// 			}
// 			if (prev_read != -1)
// 			{
// 				if (dup2(prev_read, STDIN_FILENO) == -1)
// 					exit(1);
// 				close(prev_read);
// 			}
// 			if (i < (n - 1))
// 			{
// 				if (dup2(fd[1], STDOUT_FILENO) == -1)
// 					exit(1);
// 				close(fd[0]);
// 				close(fd[1]);
// 			}
// 			cmds[i]->here = ft_first_ft_redirections(cmds[i], cmds[i]->here, sh);
// 			if (is_builtin(cmds[i]))
// 			{
// 				builtins = ft_exec_builtins(cmds[i], sh, false);
// 				clean_children(sh);
// 				exit(builtins);
// 			}
// 			else
// 			{
// 				exec_external(cmds[i], sh);
// 				clean_children(sh);
// 				exit(127);
// 			}
// 		}
// 		pids[i] = pid;
// 		if (prev_read != -1)
// 			close(prev_read);
// 		if (i < (n - 1))
// 		{
// 			close(fd[1]);
// 			prev_read = fd[0];
// 		}
// 		else
// 			prev_read = -1;
// 		status = 0;
// 		last_pid = 0;
// 		waitpid(pids[i], &status, 0);
// 		if (i == (n - 1))
// 			last_pid = extract_exit_status(status);
// 		i++;
// 	}
// 	if (prev_read != -1)
// 		close(prev_read);
// 	sh->last_status = last_pid;
// 	free(pids);
// 	free(cmds);
// }

void	run_pipes(t_cmd *head, t_shell *sh)
{
	int		fd[2];
	int		i;
	int		n;
	int		prev_read;
	int		status;
	int		last_status;
	int		builtins;
	t_cmd	*current;
	// t_cmd	*hd;
	pid_t	wait_child;
	pid_t	pid;
	pid_t	last_pid;

	n = 0;
	prev_read = -1;
	last_pid = -1;
	current = head;
	i = 0;
	current = *ft_test_heredoc_pipes(i, n, &current, sh);
	while (current)
	{
		if (current->next && pipe(fd) == -1)
		{
			if (prev_read != -1)
				close (prev_read);
			_exit(1);
		}
		pid = fork();
		if (pid == -1)
		{
			if (current->next)
			{
				close(fd[0]);
				close(fd[1]);
			}
			if (prev_read != -1)
				close(prev_read);
			_exit (1);
		}
		if (pid == 0)
		{
			if (current->here != -2)
			{
				if (dup2(current->here, STDIN_FILENO) == -1)
					exit(1);
				if (current->fd_int_put != -2)
					close(current->here);
			}
			if (prev_read != -1)
			{
				if (dup2(prev_read, STDIN_FILENO) == -1)
					_exit(1);
				close(prev_read);
			}
			if (current->next)
			{
				if (dup2(fd[1], STDOUT_FILENO) == -1)
					_exit(1);
				close(fd[0]);
				close(fd[1]);
			}
			current->here = ft_first_ft_redirections(current, current->here, sh);
			if (is_builtin(current))
			{
				builtins = ft_exec_builtins(current, sh, false);
				clean_children(sh);
				_exit(builtins);
			}
			else
			{
				exec_external(current, sh);
				clean_children(sh);
				_exit(127);
			}
		}
		n++;
		if (prev_read != -1)
			close(prev_read);
		if (current->next)
		{
			close(fd[1]);
			prev_read = fd[0];
		}
		else
			prev_read = -1;
		last_pid = pid;
		current = current->next;
	}
	if (prev_read != -1)
		close(prev_read);
	i = 0;
	status = 0;
	last_status = 0;
	while (i < n)
	{
		wait_child = wait(&status);
		if (wait_child == -1)
		{
			if (errno == EINTR)
				continue ;
			break ;
		}
		if (wait_child == last_pid)
			last_status = extract_exit_status(status);
		i++;
	}
	sh->last_status = last_status;
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

// void	exec_cmd_line(t_shell *stru)
// {
// 	t_cmd	*head;

// 	auto int n, fd_stdin = dup(0), fd_stdout, fd = 0;
// 	fd_stdout = dup(1);
// 	reconstruct_path_dirs(stru);
// 	head = stru->commande;
// 	n = count_maillons(head);
// 	if (n == 0)
// 		return ;
// 	if (n == 1)
// 	{
// 		fd = ft_first_ft_redirections(head, fd, stru);
// 		if (is_builtin(head))
// 			(void)ft_exec_builtins(head, stru, true);
// 		else
// 			run_external(head, stru, fd);
// 		ft_close_fd(head, fd_stdin, fd_stdout, fd);
// 		if (stru->should_exit)
// 			return ;
// 	}
// 	if (n >= 2)
// 	{
// 		run_pipes(head, stru);
// 		ft_close_fd(head, fd_stdin, fd_stdout, fd);
// 	}
// 	return ;
// }

void	exec_cmd_line(t_shell *stru)
{
	t_cmd	*head;
	int		builtins;

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
			builtins = ft_exec_builtins(head, stru, true);
			if (stru->should_exit)
			{
				stru->last_status = builtins;
				return ;
			}

		}
		else
			run_external(head, stru, fd);
		ft_close_fd(head, fd_stdin, fd_stdout, fd);
	}
	if (n >= 2)
	{
		run_pipes(head, stru);
		ft_close_fd(head, fd_stdin, fd_stdout, fd);
	}
	return ;
}
