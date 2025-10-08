/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:39:18 by agouin            #+#    #+#             */
/*   Updated: 2025/10/08 11:39:03 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_builtins(t_cmd *commande, t_shell *stru, bool cmd_seule)
{
	int	status;

	status = 0;
	if (ft_strncmp(commande->cmd, "pwd", 4) == 0)
		status = ft_pwd(commande->args, stru);
	else if (ft_strncmp(commande->cmd, "cd", 3) == 0)
		status = ft_cd(commande->args, stru);
	else if (ft_strncmp(commande->cmd, "echo", 5) == 0)
		status = ft_echo(commande->args);
	else if (ft_strncmp(commande->cmd, "env", 4) == 0)
		status = ft_env(stru->environ);
	else if (ft_strncmp(commande->cmd, "exit", 5) == 0)
		status = ft_exit(stru, commande->args, cmd_seule);
	else if (ft_strncmp(commande->cmd, "unset", 5) == 0)
		status = ft_unset(stru, commande->args);
	else if (ft_strncmp(commande->cmd, "export", 5) == 0)
		status = ft_export(commande->args, &stru->environ, &stru->local, stru);
	else
		return (1);
	stru->last_status = status;
	return (status);
}

int main(int argc, char **argv, char **env)
{
	char	*rl;
	t_shell	stru;
	int		syntax;
	int		status;
	// t_split	*split = NULL;

	(void)argc;
	(void)argv;
	ft_bzero(&stru, sizeof(stru));
	stru.environ = ft_duplicate_env(env, &stru);
	update_shlvl(stru.environ, &stru);
	// ft_init_fd1();
	while (!stru.should_exit)
	{
		ft_signal();
		rl = readline("\033[32mMinishell : \033[0m");
		if (!rl)
		{
			write(1, "exit\n", 5);
			clean_all(&stru);
			stru.should_exit = 1;
			break ;
		}
		if (*rl)
			add_history(rl);
		stru.tokens = ft_tokenisation(rl, stru.tokens);
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
