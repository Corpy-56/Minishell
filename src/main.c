/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:39:18 by agouin            #+#    #+#             */
/*   Updated: 2025/07/18 17:45:14 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

////il faut compiler avec cc main.c -lreadline
int	ft_error(int i, char *str)
{
	i = 0;
	//write(2, "Error\n", 7);
	write(2, str, (ft_strlen(str)));
	write(2, "\n", 1);
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
	if (ft_strncmp(str, "ls", 3) == 0 || ft_strncmp(str, "cat", 4) == 0
		|| ft_strncmp(str, "grep", 5) == 0 || ft_strncmp(str, "wc", 3) == 0 
		|| ft_strncmp(str, "head", 5) == 0 || ft_strncmp(str, "tail", 5) == 0 
		|| ft_strncmp(str, "date", 5) == 0 || ft_strncmp(str, "sleep", 6) == 0
		|| ft_strncmp(str, "echo", 5) == 0 || ft_strncmp(str, "cd", 3) == 0
		|| ft_strncmp(str, "pwd", 4) == 0 || ft_strncmp(str, "export", 7) == 0
		|| ft_strncmp(str, "unset", 6) == 0 || ft_strncmp(str, "env", 4) == 0
		|| ft_strncmp(str, "exit", 5))
			return (0);
	return (1);
}
void	ft_initialization_commande(t_cmd *commande)
{
	commande->args = NULL;
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
	commande = ft_calloc(sizeof(t_cmd), 1);
	if (commande == NULL)
		return ;// faire une vrai sorti
	ft_initialization_commande(commande);
	p_actuel = b_debut;
	while (p_actuel)
	{
		if (ft_strncmp(p_actuel->str, "<<", 2) == 0)// && commande->heredoc == NULL)
		{
			if (commande->heredoc == NULL)
				commande->heredoc = ft_strdup(p_actuel->next->str);
			else if (p_actuel->next->str != NULL && commande->heredoc != NULL)// problematique car prend les "  "
			{
				
				ft_strjoin(commande->heredoc, p_actuel->next->str);
			}
		}
		else if (commande->heredoc != NULL && ft_strncmp(p_actuel->str, "<<", 2) == 0)
		{
			//commande = ft_calloc(sizeof(t_cmd), 1);
			//if (commande == NULL)
			//	return ;
			//commande->next = NULL;	
			//if (a_debut == NULL)
			//{
			//	a_debut = commande;
			//	fin = commande;
			//}
			//else
			//{
			//	fin->next = commande;
			//	fin = commande;
			//}
			//if (p_actuel->next->str != NULL)
			//	commande->heredoc = ft_strdup(p_actuel->next->str);
		}
		else if (ft_strncmp(p_actuel->str, ">>", 2) == 0) // remplace automatiquement celui que je veyx pas
		{
			if (commande->fd_int_put != -2)
				commande->fd_int_put = 0;
			commande->fd_int_put = open(p_actuel->next->str, O_CREAT | O_WRONLY, 0777);
			if (commande->fd_int_put == -1)
				return ; //faire une vrai sortie
			p_actuel = p_actuel->next;
			printf("%d", commande->fd_int_put);
		}
		else if (ft_strncmp(p_actuel->str, "<", 1) == 0) // remplace automatiquement celui que je veyx pas
		{
			if (commande->fd_int_put != -2)
				commande->fd_int_put = 0;// faire une condition si pas de str
			commande->fd_int_put = open(p_actuel->next->str, O_CREAT | O_WRONLY, 0777);
			if (commande->fd_int_put == -1)
			{
				printf("%s: Permission denied\n", p_actuel->next->str); //si besoin je peux faire un char * pour le nom du fichier
				return ; //faire une vrai sortie
			}
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
		//else if (ft_strncmp(p_actuel->str, "|", 1) == 0)
		//{
		//	commande = ft_calloc(sizeof(t_cmd), 1);
		//	if (commande == NULL)
		//		return ;
		//	commande->next = NULL;	
		//	if (a_debut == NULL)
		//	{ft_strncmp(p_actuel->str, ">>", 2) == 0
		//		a_debut = commande;
		//		fin = commande;
		//	}
		//	else
		//	{
		//		fin->next = commande;
		//		fin = commande;
		//	}
		//}
		//else
		//	commande->args = ft_strjoin_tab(commande->args, commande->cmd);
		// je peux le lier avcec les heredocs car je dois faire le heredoc
		p_actuel = p_actuel->next;
	}
}

int	ft_next_redirection(char *str)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	while((str[i] == '<' || str[i] == '>') && str[i])
		i++;
	if (str[i] == '\0')
		return (1);
	while (str[i])
	{
		j = ft_isalnum(str[i]);
		i++;
		if (j == 0)
			return (1);
	}
	return (0);
}

void	ft_valid_syntax(t_tokens *token)
{
	t_tokens	*p_actuel;

	p_actuel = token;
	if (ft_strncmp(p_actuel->str, "|", 2) == 0)
		ft_error(1, "syntax error near unexpected token `|'");
	while(p_actuel != NULL)
	{
		if (p_actuel->next == NULL && ft_strncmp(p_actuel->str, "|", 1) == 0)
			ft_error(1, "syntax error near unexpected token `|'");
		else if (ft_strncmp(p_actuel->str, ">>>", 4) == 0 || ft_strncmp(p_actuel->str, "<<<", 4) == 0)
			ft_error(1, "syntax error near unexpected token");
		else if (ft_strncmp(p_actuel->str, ">>>>", 4) == 0 || ft_strncmp(p_actuel->str, "<<<<", 4) == 0)
			ft_error(1, "syntax error near unexpected token");
		else if (ft_strncmp(p_actuel->str, ">>", 2) == 0 || ft_strncmp(p_actuel->str, "<<", 2) == 0)
		{
			if (p_actuel->next == NULL && ft_next_redirection(p_actuel->str) == 1)
				ft_error(1, "syntax error near unexpected token");
		}
		else if (ft_strncmp(p_actuel->str, ">", 1) == 0 || ft_strncmp(p_actuel->str, "<", 1) == 0)
		{
			if (p_actuel->next == NULL && ft_next_redirection(p_actuel->str) == 1)
				ft_error(1, "syntax error near unexpected token");
		}
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
	stru = ft_calloc(sizeof(t_shell), 1);
	if (stru == NULL)
		return (0);
	stru->environ = ft_duplicate_env(env);
	while(1)
	{
		rl = readline("Minishell : ");
		if(!rl)
			exit(0);//besoin dune fonction pour free
		add_history(rl);
		stru->tokens = ft_tokenisation(rl, stru->tokens);
		ft_valid_syntax(stru->tokens);
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
	rl_clear_history ();
    return (0);
}

