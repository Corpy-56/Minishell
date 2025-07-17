/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:39:18 by agouin            #+#    #+#             */
/*   Updated: 2025/07/17 10:07:40 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//il faut compiler avec cc main.c -lreadline

/* int	main(int argc, char **argv, char **env)
{
	char	*rl;
	//t_tokens	**args;
	t_shell	*stru;

	(void)argc;
	(void)argv;
	//args = ft_tokenisation(rl, args);
	stru = malloc(sizeof(t_shell));
	if (stru == NULL)
		return (0);
	stru->environ = ft_duplicate_env(env);
	while (1)
	{
		rl = readline("Minishell > ");
		if (!rl)
			exit(0);//besoin dune fonction pour free
		add_history(rl);
		stru->tokens = ft_tokenisation(rl, stru->tokens);
		ft_pwd(rl);
		ft_env(rl);
		ft_exit(rl, stru->tokens);
		ft_echo(rl, stru->tokens); 
		ft_cd(rl, stru->tokens);
	}
	return (0);
} */

/* int	main(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("before chdir: %s\n", pwd);
	chdir("..");
	pwd = getcwd(NULL, 0);
	printf("after chdrir: %s\n", pwd);
	return (0);
} */

int main(int argc, char **argv, char **env)
{
	char *rl;
	t_shell	*stru;
	t_tokens *tmp;

	(void)argc;
	(void)argv;
	stru = ft_calloc(1, sizeof(t_shell));
	if (stru == NULL)
		return (0);
	tmp = stru->tokens;
	stru->environ = ft_duplicate_env(env);
	while (1)
	{
		rl = readline("Minishell > ");
		if (!rl)
			exit(0);//besoin dune fonction pour free
		if (*rl)
			add_history(rl);
		stru->tokens = ft_tokenisation(rl, stru->tokens);
		//free(rl);
		if (!stru->tokens)
			continue ;
		stru->tokens->args = args_from_tokens(stru->tokens);
		while (tmp != NULL)
		{
			printf("%s\n", tmp->str);
			tmp = stru->tokens; //je stocke mes tokens dans tmp que je renouvelle a chaque fois
		}
		if (ft_strncmp(stru->tokens->args[0], "pwd", 4) == 0)
			ft_pwd(stru->tokens->args);
		else if (ft_strncmp(stru->tokens->args[0], "cd", 3) == 0)
			ft_cd(stru->tokens->args);
		else if (ft_strncmp(stru->tokens->args[0], "echo", 5) == 0)
			ft_echo(stru->tokens->args);
		else if (ft_strncmp(rl, "env", 4) == 0)
			ft_env(stru);
		else if (ft_strncmp(stru->tokens->args[0], "exit", 5) == 0)
			ft_exit(stru->tokens->args);
		// free_args(stru->tokens->args);
		// free_tokens(stru->tokens);
		free(rl);
	}
	rl_clear_history (); // pas oublier dans le exit et controle C 
    return (0);
}

