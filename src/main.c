/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:39:18 by agouin            #+#    #+#             */
/*   Updated: 2025/09/26 13:35:43 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_test_bultins(t_cmd *commande, t_shell *stru)
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
		status = ft_exit(stru, commande->args);
	else if (ft_strncmp(commande->cmd, "unset", 5) == 0)
		status = ft_unset(stru, commande->args);
	else if (ft_strncmp(commande->cmd, "export", 5) == 0)
		status = ft_export(commande->args, &stru->environ, &stru->local);
	else
		return (1);
	stru->last_status = status;
	return (0);
}

// void	ft_test_bultins(t_cmd *commande, t_shell *stru)
// {
// 	int	status;

// 	status = 0;
// 	if (ft_strncmp(commande->cmd, "pwd", 4) == 0)
// 		status = ft_pwd(commande->args, stru);
// 	else if (ft_strncmp(commande->cmd, "cd", 3) == 0)
// 		status = ft_cd(commande->args);
// 	else if (ft_strncmp(commande->cmd, "echo", 5) == 0)
// 		status = ft_echo(commande->args);
// 	else if (ft_strncmp(commande->cmd, "env", 4) == 0)
// 		status = ft_env(stru->environ);
// 	else if (ft_strncmp(commande->cmd, "exit", 5) == 0)
// 		status = ft_exit(stru, commande->args);
// 	else if (ft_strncmp(commande->cmd, "unset", 5) == 0)
// 		status = ft_unset(stru, commande->args);
// 	else if (ft_strncmp(commande->cmd, "export", 5) == 0)
// 		status = ft_export(commande->args, &stru->environ, &stru->local);
// 	// else
// 	// 	return (1);
// 	stru->last_status = status;
// 	// return (0);
// }


/* void	ft_on_exect(t_cmd *commande, t_shell *stru)
{
	t_cmd	*a_debut;

	a_debut = commande;
	while (a_debut)
	{
		if (commande->cmd != NULL)
			ft_test_bultins(commande, stru); //on peut aussi mettre le exceve
		a_debut = a_debut->next;
	}
} */

// void	ft_on_exect(t_cmd *commande, t_shell *stru, char **env)
// {
// 	t_cmd	*a_debut;

// 	a_debut = commande;
// 	while (a_debut)
// 	{
// 		if (commande->cmd != NULL)
// 		{
// 			if (!ft_test_bultins(commande, stru))
// 				run_external(commande, stru, env);
// 		}
// 		a_debut = a_debut->next;
// 	}
// }
int main(int argc, char **argv, char **env)
{
	char *rl;
	t_shell	*stru;
	int	syntax;
	int	status;

	(void)argc;
	(void)argv;
	stru = ft_calloc(1, sizeof(t_shell));
	if (stru == NULL)
		return (0);
	stru->environ = ft_duplicate_env(env, stru);
	while (!stru->should_exit)
	{
		ft_signal();
		rl = readline("Minishell > ");
		if (!rl)
		{
			write(1, "exit\n", 5);
			// stru->last_status = 1;
			stru->should_exit = 1;
			// ft_exit_d(); // je suis pas sur voir avec Sarah
			break ;
		}
		if (*rl)
			add_history(rl);
  //j      stru->tokens = NULL;
		stru->tokens = ft_tokenisation(rl, stru->tokens);
		free(rl);
		if (!stru->tokens)
			continue ;
		// stru->tokens->args = args_from_tokens(stru->tokens);
		main_expand(stru);
		split_all_tokens(stru->tokens, stru);
		unquote_tokens(stru->tokens);
		if (stru->tokens != NULL)
		{
			// if (ft_valid_syntax(stru->tokens) != -1)
			// {
			// 	stru->commande = ft_type_token(stru->commande, stru->tokens, stru);
			// 	stru->commande = suppr_empty_cmd(stru->commande);
			// 	if (stru->commande == NULL)
			// 	{

			// 		clean_cmd(stru);
			// 		continue ;
			// 	}
			// //	if (main_variables(stru) == 1)
			// //		continue ;
			// 	// exec_cmd_line(stru, env);
			// 	ft_on_exect(stru->commande, stru, env);
			// }
			syntax = ft_valid_syntax(stru->tokens);
			if (syntax != 0)
			{
				stru->last_status = 258;
				clean_cmd(stru);
				continue ;
			}
			stru->commande = ft_type_token(stru->commande, stru->tokens, stru);
			stru->commande = suppr_empty_cmd(stru->commande);
			if (stru->commande == NULL)
			{
				clean_cmd(stru);
				continue ;
			}
			exec_cmd_line(stru, env);
			if (stru->should_exit)
			{
				clean_cmd(stru);
				break ;
			}
		}
		clean_cmd(stru);
	}
	status = stru->last_status;
	clean_all(stru);
	free(stru);
	// return (0);
	exit (status);
}
