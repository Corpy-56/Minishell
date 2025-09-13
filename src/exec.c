/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:33:30 by skuor             #+#    #+#             */
/*   Updated: 2025/09/13 19:20:34 by skuor            ###   ########.fr       */
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
		cmd = cmd ->next;
	}
	return (n);
}

void	run_two(t_cmd *cmd_a, t_cmd *cmd_b, t_shell *sh, char **env)
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
}

void	exec_cmd_line(t_shell *stru, char **env)
{
	t_cmd	*head;
	int		n;

	head = stru->commande;
	n = count_maillons(head);
	if (n == 0)
		return ;
	if (n == 1)
	{
		if (is_builtin(head))
			stru->last_status = ft_test_bultins(head, stru);
		else
			run_external(head, stru, env);
		return ;
	}
	if (n == 2)
	{
		run_two(head, head->next, stru, env);
		return ;
	}
}
