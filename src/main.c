/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:39:18 by agouin            #+#    #+#             */
/*   Updated: 2025/07/31 18:00:02 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error(int i, char *str, char *str2)
{
	i = 0;
	if (str2 != NULL)
		write(2, str2, (ft_strlen(str)));
	write(2, str, (ft_strlen(str)));
	return (-1);
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


int	ft_test_commande(char *str)// na aucune utilite puisque on va utiliser exceve
{
	char quote;
	char *temp;
	int	i;

	i = 0;
	quote = '\0';
	temp = NULL;
	if (str[0] == '\"' || str[0] == '\'')
	{
		quote = str[i++];
		while (str[i] && str[i] != quote)
			temp = ft_strjoin_char(temp, str[i++]);
		temp[i] = '\0';
	}
	else
		temp = ft_strdup(str);
	if (ft_strncmp(temp, "ls", 3) == 0 || ft_strncmp(temp, "cat", 4) == 0
		|| ft_strncmp(temp, "grep", 5) == 0 || ft_strncmp(temp, "wc", 3) == 0 
		|| ft_strncmp(temp, "head", 5) == 0 || ft_strncmp(temp, "tail", 5) == 0 
		|| ft_strncmp(temp, "date", 5) == 0 || ft_strncmp(temp, "sleep", 6) == 0
		|| ft_strncmp(temp, "echo", 5) == 0 || ft_strncmp(temp, "cd", 3) == 0
		|| ft_strncmp(temp, "pwd", 4) == 0 || ft_strncmp(temp, "export", 7) == 0
		|| ft_strncmp(temp, "unset", 6) == 0 || ft_strncmp(temp, "env", 4) == 0
		|| ft_strncmp(temp, "exit", 5) == 0)
		{
			free(temp);
			return (0);
		}
	return (1);
}

void	ft_initialization_commande(t_cmd *commande)
{
	commande->args = NULL;
	commande->heredoc = NULL;
	commande->fd_int_put = -2;
	commande->next = NULL;
	commande->fd_out_put1 = -2;
	commande->fd_out_put2 = -2;
	return ;
}


int ft_is_str_isprint(char *str)
{
	int i;
	int	j;

	j = 1;
	i = 0;
	while (str[i] && j == 1)
	{
		j = ft_isprint(str[i]);
		i++;
	}
	if (j == 1)
		return (1);
	return (0);
}

int ft_nb_args(t_tokens *token)
{
	t_tokens *p_actuel;
	int	j;

	j = 0;
	p_actuel = token;
	while (p_actuel)
	{
		if (p_actuel->str[0] == '<' && p_actuel->str[0] == '>')
			p_actuel = p_actuel->next;
		else if (p_actuel->str[0] == '|')
			return (j);
		else if (ft_is_str_isprint(p_actuel->str) == 1 && p_actuel != NULL)
			j++;
		p_actuel = p_actuel->next;
	}
	return (j);
}


void	ft_printf_tab(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		printf("%s\n", args[i]);
		i++;
	}
}

void	ft_type_token(t_cmd *commande, t_tokens *b_debut)
{
	t_tokens	*p_actuel;
	int	i;
	t_tokens	*a_debut;
	t_tokens	*fin;
	
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
		if (ft_strncmp(p_actuel->str, ">", 2) == 0)
		{
			if (commande->fd_out_put1 != -2)
				close(commande->fd_out_put1);
			else if (p_actuel->next->str != NULL)
				commande->fd_out_put1 = open(p_actuel->next->str, O_CREAT | O_WRONLY, 0777);
			if (commande->fd_out_put1 == -1)
				ft_error(1, ": Permission denied\n", p_actuel->next->str) ;
			p_actuel = p_actuel->next;
		}
		else if (ft_strncmp(p_actuel->str, ">>", 3) == 0)
		{
			if (commande->fd_out_put2 != -2)
				close(commande->fd_out_put2);
			else if (p_actuel->next->str != NULL)
				commande->fd_out_put2 = open(p_actuel->next->str, O_CREAT | O_WRONLY, 0777);
			if (commande->fd_out_put2 == -1)
				ft_error(1, ": Permission denied\n", p_actuel->next->str) ;
			p_actuel = p_actuel->next;
		}
		else if (ft_strncmp(p_actuel->str, "<", 2) == 0)
		{
			if (commande->fd_int_put != -2)
				close(commande->fd_int_put);
			else if (p_actuel->next->str != NULL)
				commande->fd_int_put = open(p_actuel->next->str, O_RDONLY, 0777);
			if (commande->fd_int_put == -1)
				ft_error(1, ": No such file or directory\n", p_actuel->next->str) ;
			p_actuel = p_actuel->next;
		}
		//else if(ft_is_str_isprint(p_actuel->str) == 1)
		//{
		//	if (commande->args == NULL && ft_test_commande(p_actuel->str) != 0)
		//	{
		//		ft_error(1, ": command not found\n", p_actuel->str);
		//		break;
		//	}
		//	else if (ft_test_commande(p_actuel->str) == 0 && commande->args == NULL)
		//	{
		//		commande->cmd = ft_calloc(sizeof(char *), ft_strlen(p_actuel->str));
		//		commande->cmd = ft_strdup(p_actuel->str);
		//	}
		//	if (commande->args == NULL)
		//		commande->args = ft_calloc(sizeof(char *), ft_nb_args(p_actuel) + 1);
		//	commande->args[i] = ft_strdup(p_actuel->str);
		//	i++;
		//}
		//else if (ft_strncmp(p_actuel->str, "|", 2) == 0)
		//{
		//	if (commande->cmd)
		//	{
		//		commande->next = NULL;
		//		if (!a_debut)
		//			a_debut = commande;
		//		else
		//			fin->next = commande;
		//		fin = commande;
		//	}
		//}
		p_actuel = p_actuel->next;
	}
	//ft_printf_tab(commande->args);
}


int	ft_valid_syntax(t_tokens *token)//gerer les / pour cd mais voir ca avec Sarah
{
	t_tokens	*p_actuel;

	p_actuel = token;
	if (ft_strncmp(p_actuel->str, "|", 1) == 0 && p_actuel)
		return (ft_error(1, "syntax error near unexpected token `|'\n", NULL));
	while(p_actuel != NULL)
	{
		if ((p_actuel->next == NULL && ft_strncmp(p_actuel->str, "|", 1) == 0) || ft_strncmp(p_actuel->str, "||", 2) == 0)
			return (ft_error(1, "syntax error near unexpected token '|'\n", NULL));
		else if (ft_strncmp(p_actuel->str, ">>>", 3) == 0 || ft_strncmp(p_actuel->str, "<<<", 3) == 0)
			return (ft_error(1, "syntax error near unexpected token\n", NULL));
		else if (ft_strncmp(p_actuel->str, ">", 1) == 0 || ft_strncmp(p_actuel->str, "<", 1) == 0)
		{
			if (p_actuel->next == NULL || ft_is_str_isprint(p_actuel->next->str) == 0)
				return (ft_error(1, "syntax error near unexpected token\n", NULL));
		}
		p_actuel = p_actuel->next;
	}
	return (0);
}


int main(int argc, char **argv, char **env)
{
	char *rl;
	t_shell	*stru;

	(void)argc;
	(void)argv;
	stru = ft_calloc(sizeof(t_shell), 1);
	stru->environ = ft_duplicate_env(env);
	if (stru == NULL)
		return (0);
	while(1)
	{
		rl = readline("Minishell : ");
		if(!rl)
			exit(0);//besoin dune fonction pour free 
		add_history(rl);
		stru->tokens = ft_tokenisation(rl, stru->tokens);
		while (stru->tokens)
		{
			printf("%s\n", stru->tokens->str);
			stru->tokens = stru->tokens->next;
		}
		//if (stru->tokens != NULL)
		//{
		//	if (ft_valid_syntax(stru->tokens) != -1)
		// 		ft_type_token(stru->commande, stru->tokens);
		//}
	}
	rl_clear_history ();
	return (0);
}

