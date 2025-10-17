/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:39:18 by agouin            #+#    #+#             */
/*   Updated: 2025/10/17 18:32:36 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tty(t_shell *stru)
{
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
	{
		clean_all(stru);
		exit (1);
	}
}

void	exit_with_status(t_shell *stru)
{
	int	status;

	status = stru->last_status;
	write(1, "exit\n", 5);
	clean_all(stru);
	exit (status);
}

int	read_and_tokenise(t_shell *stru)
{
	char	*rl;

	ft_signal();
	if (isatty(stru->dup_1) != 1 && stru->dup_1 == -1)
		stru->dup_1 = dup(STDOUT_FILENO);
	if (isatty(stru->dup_0) != 1 && stru->dup_0 == -1)
		stru->dup_0 = dup(0);
	rl = readline(MINISHELL);
	if (!rl)
		exit_with_status(stru);
	if (*rl)
		add_history(rl);
	if(ft_strlen(rl) > 1000)
	{
		ft_putstr_fd("minishell: line too long\n", 2);
		return (0);
	}
	stru->tokens = ft_tokenisation(rl, stru->tokens, 0);
	free(rl);
	if (!stru->tokens)
		return (0);
	main_expand(stru);
	split_all_tokens(&stru->tokens, stru);
	unquote_tokens(stru->tokens);
	return (1);
}

int	parse_cmds(t_shell *stru)
{
	int	syntax;

	syntax = ft_valid_syntax(stru->tokens);
	if (syntax != 0)
	{
		stru->last_status = 2;
		return (0);
	}
	stru->commande = ft_type_token(stru->commande, stru->tokens, stru);
	stru->commande = suppr_empty_cmd(stru->commande);
	return (stru->commande != NULL);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	stru;
	int		status;

	ft_bzero(&stru, sizeof(stru));
	init_shell(&stru, env, argc, argv);
	while (!stru.should_exit)
	{
		if (!read_and_tokenise(&stru))
		{
			clean_cmd(&stru);
			continue ;
		}
		if (!parse_cmds(&stru))
		{
			clean_cmd(&stru);
			continue ;
		}
		exec_cmd_line(&stru);
		clean_cmd(&stru);
	}
	if (stru.dup_0 >= 0)
		close (stru.dup_0);
	if (stru.dup_1 >= 0)
		close (stru.dup_1);
	status = stru.last_status;
	clean_all(&stru);
	exit (status);
}
