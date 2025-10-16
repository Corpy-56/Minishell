/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:33:30 by skuor             #+#    #+#             */
/*   Updated: 2025/10/16 16:12:49 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reconstruct_path_dirs(t_shell *stru)
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

void	end_of_line_restore(int *saved_in, int *saved_out)
{
	if (*saved_in != -1)
	{
		dup2(*saved_in, 0);
		if (*saved_in > 2)
			close_fds(saved_in);
		*saved_in = -1;
	}
	if (*saved_out != -1)
	{
		dup2(*saved_out, 1);
		if (*saved_out > 2)
			close_fds(saved_out);
		*saved_out = -1;
	}
}

void	status_signals(t_shell *stru, int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			apply_cmd_redirs_in_child(stru->commande, stru);
			end_of_line_restore(&stru->dup_0, &stru->dup_1);
			write(1, "^C\n", 3);
		}
	}
	ft_signal();
	stru->last_status = extract_exit_status(status);
}

void	run_one_cmd(t_exec *exec, t_shell *stru)
{
	int	builtins;

	builtins = 0;
	static_struct(stru);
	exec->fd = ft_first_ft_redirections(exec->head, exec->fd, stru);
	if (exec->fd == -1)
		return ;
	if (is_builtin(exec->head))
	{
		builtins = ft_exec_builtins(exec->head, stru, true);
		stru->last_status = builtins;
		apply_cmd_redirs_in_child(exec->head, stru); // ajoute
		end_of_line_restore(&exec->fd_stdin, &exec->fd_stdout);
		return ;
	}
	if (exec->head->args == NULL)
	{
		stru->last_status = 0;
		end_of_line_restore(&exec->fd_stdin, &exec->fd_stdout);
		return ;
	}
	exec->status = run_external(exec->head, stru, exec->fd);
	status_signals(stru, exec->status);
	apply_cmd_redirs_in_child(exec->head, stru);
	end_of_line_restore(&exec->fd_stdin, &exec->fd_stdout);
}

void	exec_cmd_line(t_shell *stru)
{
	t_exec	exec;

	reconstruct_path_dirs(stru);
	init_exec(&exec, stru);
	if (exec.n == 0)
	{
		end_of_line_restore(&exec.fd_stdin, &exec.fd_stdout);
		return ;
	}
	if (exec.n == 1)
		run_one_cmd(&exec, stru);
	else
		run_pipes(exec.head, stru);
	end_of_line_restore(&exec.fd_stdin, &exec.fd_stdout);
}

