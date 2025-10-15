/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:39:18 by agouin            #+#    #+#             */
/*   Updated: 2025/10/15 14:10:42 by skuor            ###   ########.fr       */
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

int main(int argc, char **argv, char **env)
{
	char	*rl;
	t_shell	stru;
	int		syntax;
	int		status;

	(void)argc; 
	(void)argv;
	ft_bzero(&stru, sizeof(stru));
	init_shell(&stru, env);
	// stru.environ = ft_duplicate_env(env, &stru);
	update_shlvl(stru.environ, &stru);
	save_termios1();
	// init_shell(&stru);
	ft_tty(&stru);
	set_shell(&stru);
	while (!stru.should_exit)
	{
		ft_signal();
		rl = readline("\033[32mMinishell : \033[0m");
		if (!rl)
		{
			status = stru.last_status;
			write(1, "exit\n", 5);
			clean_all(&stru);
			exit(status);
		}
		if (*rl)
			add_history(rl);
		stru.tokens = ft_tokenisation(rl, stru.tokens, 0);
		free(rl);
		if (!stru.tokens)
			continue ;
		main_expand(&stru);
		split_all_tokens(&stru.tokens, &stru);
		unquote_tokens(stru.tokens);
		if (stru.tokens != NULL)
		{
			syntax = ft_valid_syntax(stru.tokens);
			if (syntax != 0)
			{
				stru.last_status = 2;
				clean_cmd(&stru);
				continue ;
			}
			stru.commande = ft_type_token(stru.commande, stru.tokens, &stru);
			stru.commande = suppr_empty_cmd(stru.commande);
			if (stru.commande == NULL)
			{
				clean_cmd(&stru);
				continue ;
			}
			exec_cmd_line(&stru);
			if (stru.should_exit)
			{
				clean_cmd(&stru);
				break ;
			}
		}
		clean_cmd(&stru);
	}
	status = stru.last_status;
	clean_all(&stru);
	exit (status);
}
