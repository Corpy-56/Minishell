/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:39:18 by agouin            #+#    #+#             */
/*   Updated: 2025/07/16 17:03:48 by agouin           ###   ########.fr       */
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


int	ft_test_commande(char *str)
{
	if (ft_strncmp(str, "ls", 2) == 0 || ft_strncmp(str, "cat", 3) == 0
		|| ft_strncmp(str, "grep", 4) == 0 || ft_strncmp(str, "wc", 2) == 0 
		|| ft_strncmp(str, "head", 4) == 0 || ft_strncmp(str, "tail", 4) == 0 
		|| ft_strncmp(str, "date", 4) == 0 || ft_strncmp(str, "sleep", 5) == 0
		|| ft_strncmp(str, "echo", 4) == 0 || ft_strncmp(str, "cd", 2) == 0
		|| ft_strncmp(str, "pwd", 3) == 0 || ft_strncmp(str, "export", 6) == 0
		|| ft_strncmp(str, "unset", 5) == 0 || ft_strncmp(str, "env", 3) == 0
		|| ft_strncmp(str, "exit", 4))
			return (0);
	return (1);
}
void	ft_initialization_commande(t_cmd *commande)
{
	commande->args = NULL;
	//if (commande->cmd != NULL)
	//{
	//	commande->cmd = NULL;
	//	free(commande->cmd);
	//}
	commande->heredoc = NULL;
	commande->fd_int_put = -2;
	commande->next = NULL;
	commande->fd_out_put = -2;	
	return ;
}

//void	ft_free_tab(char **tab)
//{
//	int	i;

//	i = 0;
//	if (tab == NULL)
//		return ;
//	while (tab[i])
//	{
//		free(tab[i]);
//		tab[i] = NULL;
//		i++;
//	}
//	free(tab);
//	return ;
//}

//char	**ft_strjoin_tab(char **tab, char *str)
//{
//	int		i;
//	char	*joined;

//	if (tab == NULL)
//	{
//		tab = malloc(sizeof(2));
//		if (tab == NULL)
//			return (NULL);
//		tab[0] = ft_strdup(str);
//		if (tab[0] == NULL)
//			return (NULL);
//		tab[1] = NULL;
//		return (tab);
//	}
//	ft_free_tab(tab);
//	tab = malloc(nb_tab(tab) + 2);
//	if (joined == NULL)
//	{
//		free(str);
//		return (NULL);
//	}
//	i = -1;
//	while (str[++i])
//		joined[i] = str[i];
//	joined[i++] = c;
//	joined[i] = '\0';
//	free(str);
//	return (joined);
//}

void	ft_type_token(t_cmd *commande, t_tokens *b_debut)// verifier que ca marche bien 
{
	t_tokens	*p_actuel;
	t_cmd	*a_debut;
	t_cmd	*fin;
	int i;

	i = 0;
	a_debut = NULL;
	fin = NULL;
	//if (commande != NULL)//je pense que pour regler les segfaults il faut sassurer que les trucs sont vides sinon tu agis en consequences 
	//{
	//	free(commande);
	//	commande = NULL;
	//}
	commande = malloc(sizeof(t_cmd));
	if (commande == NULL)
		return ;// faire une vrai sorti
	ft_initialization_commande(commande);
	p_actuel = b_debut;
	while (p_actuel)
	{
		if (ft_strncmp(p_actuel->str, "<<", 2) == 0 && commande->heredoc == NULL)
		{
			if (p_actuel->next->str != NULL)
				commande->heredoc = ft_strdup(p_actuel->next->str);
		}
		else if (commande->heredoc != NULL && ft_strncmp(p_actuel->str, "<<", 2) == 0)
		{
			commande = malloc(sizeof(t_cmd));
			if (commande == NULL)
				return ;
			commande->next = NULL;	
			if (a_debut == NULL)
			{
				a_debut = commande;
				fin = commande;
			}
			else
			{
				fin->next = commande;
				fin = commande;
			}
			if (p_actuel->next->str != NULL)
				commande->heredoc = ft_strdup(p_actuel->next->str);
		}
		else if (ft_strncmp(p_actuel->str, "<", 1) == 0) // remplace automatiquement celui que je veyx pas
		{
			//if (commande->fd_int_put != -2)
				
			commande->fd_int_put = open(p_actuel->next->str, O_CREAT | O_WRONLY, 0777);
			if (commande->fd_int_put == -1)
				return ; //faire une vrai sortie
			p_actuel = p_actuel->next;
		}
		//else if (ft_strncmp(p_actuel->str, ">>", 2) == 0)
		//	commande->out_put = p_actuel->next->str;
		//else if (ft_strncmp(p_actuel->str, ">", 1) == 0)// je sais pas si je dois faire la meme chose quavec les heredocs
		//	commande->out_put = p_actuel->next->str;
		else if (ft_test_commande(p_actuel->str) == 0 && commande->cmd == NULL)// marchera si un arg mais si plusieurs
		{
			commande->cmd = ft_strdup(p_actuel->str);
			//commande->args = ft_strjoin_tab(commande->args, commande->cmd);
		}
		else if (ft_strncmp(p_actuel->str, "|", 1) == 0)
		{
			commande = malloc(sizeof(t_cmd));
			if (commande == NULL)
				return ;
			commande->next = NULL;	
			if (a_debut == NULL)
			{
				a_debut = commande;
				fin = commande;
			}
			else
			{
				fin->next = commande;
				fin = commande;
			}
		}
		//else
		//	commande->args = ft_strjoin_tab(commande->args, commande->cmd);
		// je peux le lier avcec les heredocs car je dois faire le heredoc
		p_actuel = p_actuel->next;
	}
}

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
		ft_type_token(stru->commande, stru->tokens);
		if(ft_strncmp(rl, "pwd", 4) == 0)
		{
			pwd = getcwd(NULL, 0);
			printf("%s\n", pwd);
		}
		if (ft_strncmp(rl, "env", 4) == 0)
		{
			while(stru->environ != NULL)
			{
				printf("%s\n", stru->environ->str);
				stru->environ = stru->environ->next;
			}
		}
	}
	rl_clear_history (); // pas oublier dans le exit et controle C 
    return (0);
}
//les commandes peuvent rater il faut quelle retourne une valeur 