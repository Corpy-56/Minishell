/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:39:18 by agouin            #+#    #+#             */
/*   Updated: 2025/07/12 09:58:58 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

////il faut compiler avec cc main.c -lreadline
int	ft_error(int i, char *str)
{
	i = 0;
	i++;
	printf("%d", i);
	write(2, "Error\n", 7);
	write(2, &str, ft_strlen(str));
	//exit(EXIT_FAILURE);
	return (0);
}

int	white_space(char *str, int i)
{
	while (str[i] != '\0' && (str[i] == 32 || str[i] == 9))
		i++;
	if (str[i] != 32 && str[i] != 9 && str[i] != '\0')
		return (i);
	else if (str[i] == '\0')
		return (-1);
	return (0);
}

//void	ft_type_token(t_tokens *token, t_cmd *commande)
//{
//	int	i;

//	i = 0;
//	while (token)
//	{
//		if (i == 0)
//		{
//			if (ft_strncmp(token->str, "<<", 2) == 0) // || ft_strncmp(token->str, ">>", 2) == 0)
//				commande->
//		}
//		i++;
//		token = token->next;
//	}

//}

int main(int argc, char **argv, char **env)
{
	char *rl;
	char *pwd;
	t_shell	*stru;

	(void)argc;
	(void)argv;
	stru = malloc(sizeof(t_shell));
	if (stru == NULL)
		return (0);
	stru->environ = ft_duplicate_env(env);
	while(1)
	{
		rl = readline("Minishell > ");
		if(!rl)
			exit(0);//besoin dune fonction pour free
		add_history(rl);
		stru->tokens = ft_tokenisation(rl, stru->tokens);
		//ft_type_token(stru->tokens, stru->commande);
		while (stru->tokens != NULL)
		{
			printf("%s\n", stru->tokens->str);
			stru->tokens = stru->tokens->next;
		}
		if(ft_strncmp(rl, "pwd", 4) == 0)
		{
			pwd = getcwd(NULL, 0);
			printf("%s\n", pwd);
		}
		if (ft_strncmp(rl, "env", 4) == 0)
		{
			int i;

			i = 0;
			while(stru->environ != NULL)
			{
				printf("%s\n", stru->environ->str);
				stru->environ = stru->environ->next;
				i++;
				printf("%d", i);
			}
		}
	}
	//rl_clear_history (); // pas oublier dans le exit et controle C 
    return (0);
}
//les commandes peuvent rater il faut quelle retourne une valeur 