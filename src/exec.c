/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:33:30 by skuor             #+#    #+#             */
/*   Updated: 2025/10/11 11:53:41 by skuor            ###   ########.fr       */
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

t_cmd	*ft_test_heredoc_pipes(t_cmd *cmds, t_shell *sh)
{
	int		fd;
	t_cmd	*p_actuel;

	fd = 0;
	p_actuel = cmds;
	while (p_actuel)
	{
		if (p_actuel->heredoc != NULL)
		{
			p_actuel->here = ft_setup_heredoc(p_actuel, sh);
			if (p_actuel->here == -1)
				return (cmds);
			p_actuel->here = ft_expand_heredoc(p_actuel->here, sh);
		}
		p_actuel = p_actuel->next;
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
// 	int		builtins;

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
// 		{
// 			builtins = ft_exec_builtins(head, stru, true);
// 			if (stru->should_exit)
// 			{
// 				stru->last_status = builtins;
// 				return ;
// 			}
// 		}
// 		else
// 			run_external(head, stru, fd);
// 		ft_close_fd(head, fd_stdin, fd_stdout, fd);
// 	}
// 	if (n >= 2)
// 	{
// 		run_pipes(head, stru);
// 		ft_close_fd(head, fd_stdin, fd_stdout, fd);
// 	}
// 	return ;
// }

// static void	exec_builtins(t_exec *exec, t_shell *stru)
// {
// 	exec->builtins = ft_exec_builtins(exec->head, stru, true);
// 	if (stru->should_exit)
// 	{
// 		stru->last_status = exec->builtins;
// 		return ;
// 	}
// }

// void	exec_cmd_line(t_shell *stru)
// {
// 	t_exec	exec;

// 	reconstruct_path_dirs(stru);
// 	init_exec(&exec, stru);
// 	if (exec.n == 0)
// 		return ;
// 	if (exec.n == 1)
// 	{
// 		exec.fd = ft_first_ft_redirections(exec.head, exec.fd, stru);
// 		if (is_builtin(exec.head))
// 		{
// 			exec.builtins = ft_exec_builtins(exec.head, stru, true);
// 			if (stru->should_exit)
// 			{
// 				stru->last_status = exec.builtins;
// 				return ;
// 			}
// 		}
// 		else
// 			run_external(exec.head, stru, exec.fd);
// 		ft_close_fd(exec.head, exec.fd_stdin, exec.fd_stdout, exec.fd);
// 	}
// 	if (exec.n >= 2)
// 	{
// 		run_pipes(exec.head, stru);
// 		ft_close_fd(exec.head, exec.fd_stdin, exec.fd_stdout, exec.fd);
// 	}
// 	return ;
// }

void	exec_cmd_line(t_shell *stru)
{
	t_exec	exec;

	reconstruct_path_dirs(stru);
	init_exec(&exec, stru);
	if (exec.n == 0)
		return ;
	if (exec.n == 1)
	{
		exec.fd = ft_first_ft_redirections(exec.head, exec.fd, stru);
		if (is_builtin(exec.head))
		{
			exec.builtins = ft_exec_builtins(exec.head, stru, true);
			if (stru->should_exit)
			{
				stru->last_status = exec.builtins;
				return ;
			}
		}
		else
		{
			exec.status = run_external(exec.head, stru, exec.fd);
			ft_close_fd(exec.head, exec.fd_stdin, exec.fd_stdout, exec.fd);
			if (WIFSIGNALED(exec.status))
			{
				if (WTERMSIG(exec.status) == SIGINT)
					write(1, "^C\n", 4);
			}
			ft_signal();
			stru->last_status = extract_exit_status(exec.status);
		}
		ft_close_fd(exec.head, exec.fd_stdin, exec.fd_stdout, exec.fd);
	}
	if (exec.n >= 2)
	{
		run_pipes(exec.head, stru);
		ft_close_fd(exec.head, exec.fd_stdin, exec.fd_stdout, exec.fd);
	}
	return ;
}