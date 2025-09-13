/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:39:18 by agouin            #+#    #+#             */
/*   Updated: 2025/09/13 18:52:53 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>

// void	ft_test_bultins(t_cmd *commande, t_shell *stru)
// {
// 	//pid_t	pid;
// 	int			status;

// 	status = 0;
// 	if (ft_strncmp(commande->cmd, "pwd", 4) == 0)
// 		status = ft_pwd(commande->args);
// 	else if (ft_strncmp(commande->cmd, "cd", 3) == 0)
// 		status = ft_cd(commande->args);
// 	else if (ft_strncmp(commande->cmd, "echo", 5) == 0)
// 		status = ft_echo(commande->args);
// 	else if (ft_strncmp(commande->cmd, "env", 4) == 0)
// 		status = ft_env(stru->environ);
// 	else if (ft_strncmp(commande->cmd, "exit", 5) == 0)
// 		status = ft_exit(commande->args);
// 	else if (ft_strncmp(commande->cmd, "unset", 5) == 0)
// 		status = ft_unset(stru, commande->args);
// 	else if (ft_strncmp(commande->cmd, "export", 5) == 0)
// 		status = ft_export(commande->args, &stru->environ, &stru->local);
// 	stru->last_status = status;
// 	/* else if (ft_strncmp(commande->cmd, "./", 2) == 0 || ft_strncmp(commande->cmd, "/", 1) == 0 )
// 	{
// 		pid = fork();
// 		if (pid == -1)
// 			return ;
// 		if (pid == 0)
// 		{
// 			execve(commande->cmd, commande->args, &stru->environ->str);
// 		//	kill(pid, SIGKILL); je pense pas quil soit vraiment necessaire peut etre plus tard quand le programme sera BIG
// 		}
// 		else if (pid > 0)
// 		{
// 			wait(NULL);
// 			return ;
// 		}
// 	} */// faut faire des gosses sinon on remplace le processus
// 	//sinon tu fais une fonction qui execute si seulement ls sinon message derreur 
// }

int	ft_test_bultins(t_cmd *commande, t_shell *stru)
{
	int	status;

	status = 0;
	if (ft_strncmp(commande->cmd, "pwd", 4) == 0)
		status = ft_pwd(commande->args);
	else if (ft_strncmp(commande->cmd, "cd", 3) == 0)
		status = ft_cd(commande->args);
	else if (ft_strncmp(commande->cmd, "echo", 5) == 0)
		status = ft_echo(commande->args);
	else if (ft_strncmp(commande->cmd, "env", 4) == 0)
		status = ft_env(stru->environ);
	else if (ft_strncmp(commande->cmd, "exit", 5) == 0)
		status = ft_exit(commande->args);
	else if (ft_strncmp(commande->cmd, "unset", 5) == 0)
		status = ft_unset(stru, commande->args);
	else if (ft_strncmp(commande->cmd, "export", 5) == 0)
		status = ft_export(commande->args, &stru->environ, &stru->local);
	else
		return (0);
	stru->last_status = status;
	return (1);
}


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

void	ft_on_exect(t_cmd *commande, t_shell *stru, char **env)
{
	t_cmd	*a_debut;

	a_debut = commande;
	while (a_debut)
	{
		if (commande->cmd != NULL)
		{
			if (!ft_test_bultins(commande, stru))
				run_external(commande, stru, env);
		}
		a_debut = a_debut->next;
	}
}

int main(int argc, char **argv, char **env)
{
	char *rl;
	t_shell	*stru;
	//t_env *local = NULL;

	(void)argc;
	(void)argv;
	stru = ft_calloc(1, sizeof(t_shell));
	if (stru == NULL)
		return (0);
	stru->environ = ft_duplicate_env(env, stru);
	while (1)
	{
		rl = readline("Minishell > ");
		if (!rl)
			exit(0);//besoin dune fonction pour free
		if (*rl)
			add_history(rl);
	//	free_tokens(stru->tokens);
        stru->tokens = NULL;
		stru->tokens = ft_tokenisation(rl, stru->tokens);
		free(rl);
		if (!stru->tokens)
			continue ;
		stru->tokens->args = args_from_tokens(stru->tokens);
		// if (main_variables(stru) == 1)
		// 	continue ;
		main_expand(stru);
		if (stru->tokens != NULL)
		{
			if (ft_valid_syntax(stru->tokens) != -1)
			{
				stru->commande = ft_type_token(stru->commande, stru->tokens);
				// dbg_print_pipeline(stru->commande);
				if (main_variables(stru) == 1)
					continue ;
				// ft_on_exect(stru->commande, stru, env);
				exec_cmd_line(stru, env);
			}
		}
	}
	//	free_args(stru->tokens->args);
	free_tokens(stru->tokens);
	clear_history();
	//	free_env(*stru->environ);
    return (0);
}



