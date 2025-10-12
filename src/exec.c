/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:33:30 by skuor             #+#    #+#             */
/*   Updated: 2025/10/12 15:38:58 by skuor            ###   ########.fr       */
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
	// int		fd;
	t_cmd	*p_actuel;

	// fd = 0;
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

static void	status_signals(t_shell *stru, int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(1, "^C\n", 4);
	}
	ft_signal();
	stru->last_status = extract_exit_status(status);
}

static void	run_one_cmd(t_exec *exec, t_shell *stru)
{
	int	builtins;

	builtins = 0;	
	exec->fd = ft_first_ft_redirections(exec->head, exec->fd, stru);
	if (exec->fd == -1)
		return ;
	if (is_builtin(exec->head))
	{
		builtins = ft_exec_builtins(exec->head, stru, true);
		stru->last_status = builtins;
		return ;
	}
	if (exec->head->args == NULL)
	{
		stru->last_status = 0;
		return ;
	}
	exec->status = run_external(exec->head, stru, exec->fd);
	status_signals(stru, exec->status);
}

void	exec_cmd_line(t_shell *stru)
{
	t_exec	exec;

	reconstruct_path_dirs(stru);
	init_exec(&exec, stru);
	if (exec.n == 0)
	{
		ft_close_fd(exec.head, exec.fd_stdin, exec.fd_stdout, exec.fd);		
		return ;
	}
	if (exec.n == 1)
	{
		run_one_cmd(&exec, stru);
		ft_close_fd(exec.head, exec.fd_stdin, exec.fd_stdout, exec.fd);
	}
	else
		run_pipes(exec.head, stru);
	ft_close_fd(exec.head, exec.fd_stdin, exec.fd_stdout, exec.fd);
}
