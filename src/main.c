/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:39:18 by agouin            #+#    #+#             */
/*   Updated: 2025/09/09 15:34:52 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>

void	ft_initialization_commande(t_cmd *commande)
{
	commande->args = NULL;
	commande->cmd = NULL;
	commande->heredoc = NULL;
	commande->fd_int_put = -2;
	commande->next = NULL;
	commande->fd_out_put1 = -2;
	commande->fd_out_put2 = -2;
	commande->next = NULL;
	return ;
}

int	ft_is_str_isprint(char *str)
{
	int	i;
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

int	ft_nb_args(t_tokens *token)
{
	t_tokens	*p_actuel;
	int			j;

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

int	ft_nb_tokens(t_tokens *p_actuel)
{
	int			i;
	t_tokens	*a_debut;

	i = 1;
	a_debut = p_actuel;
	while (a_debut && a_debut->str[0] != '|')
	{
		i++;
		a_debut = a_debut->next;
	}
	return (i);
}

t_cmd	*lexer_cmd(t_cmd *commande, t_tokens *p_actuel)
{
	int	i;
	int	j;

	i = ft_nb_tokens(p_actuel);
	j = 0;
	if (commande->cmd == NULL)
	{
		commande->cmd = ft_strdup(p_actuel->str);
		commande->args = ft_calloc(sizeof(char *), i);
		commande->args[0] = ft_strdup(p_actuel->str);
		j = 1;
		commande->args[j] = NULL;
	}
	else if (commande->cmd != NULL)
	{
		while (commande->args[j] != NULL)
			j++;
		commande->args[j] = ft_strdup(p_actuel->str);
		j++;
		commande->args[j] = NULL;
	}
	return (commande);
}


t_cmd	*ft_creat_token2(void)
{
	t_cmd	*commande;

	commande = ft_calloc(sizeof(t_cmd), 1);
	if (!commande)
		return (NULL);
	ft_initialization_commande(commande);
	return (commande);
}

void	ft_printf_a_debut(t_cmd *a_debut)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (a_debut)
	{
		i = 0;
		if (j > 0)
			printf("Changement de pipe\n");
		if (a_debut->args != NULL)
		{
			while (a_debut->args[i])
				printf("Argument : %s\n", a_debut->args[i++]);	
		}
		i = 0;
		if (a_debut->heredoc != NULL)
		{
			while (a_debut->heredoc[i])
				printf("heredoc : %c\n", a_debut->heredoc[i++]);
		}
		if (a_debut->fd_int_put > 0)
			printf("fd : %d\n", a_debut->fd_int_put);
		if (a_debut->fd_out_put2 > 0)
			printf("fd : %d\n", a_debut->fd_out_put2);
		if (a_debut->fd_out_put1 > 0)
			printf("fd : %d\n", a_debut->fd_out_put1);
		j++;
		a_debut = a_debut->next;
	}
}

t_tokens	*ft_test_stdout(t_cmd *cmd, t_tokens *p_temp)
{
	t_tokens	*p_a;

	p_a = p_temp;
	if (ft_strncmp(p_a->str, ">", 2) == 0)
	{
		if (cmd->fd_out_put1 != -2)
			close(cmd->fd_out_put1);
		if (p_a->next->str != NULL)
			cmd->fd_out_put1 = open(p_a->next->str, O_CREAT | O_WRONLY, 0777);
		if (cmd->fd_out_put1 == -1)
			ft_error(1, ": Permission denied\n", p_a->next->str);
	}
	else if (ft_strncmp(p_a->str, ">>", 3) == 0)
	{
		if (cmd->fd_out_put2 != -2)
			close(cmd->fd_out_put2);
		if (p_a->next->str != NULL)
			cmd->fd_out_put2 = open(p_a->next->str, O_CREAT | O_WRONLY, 0777);
		if (cmd->fd_out_put2 == -1)
			ft_error(1, ": Permission denied\n", p_a->next->str);
	}
	return (p_temp->next);
}

t_tokens	*ft_heredoc_lexer(t_tokens *p_actuel, t_cmd *commande)
{
	int	i;
	t_tokens *a_debut;

	i = 0;
	a_debut = p_actuel;
	if (commande->heredoc == NULL)
	{
		while (a_debut)
		{
			if (ft_strncmp(a_debut->str, "<<", 3) == 0)
				i++;
			a_debut = a_debut->next;
		}
		commande->heredoc = ft_calloc(sizeof(char *), i + 1);
		a_debut = p_actuel;
	}
	if (a_debut != NULL)
	{
		i = 0;
		while (commande->heredoc[i])
			i++;
		if (a_debut->next->str != NULL)
			commande->heredoc[i] = *ft_strdup(a_debut->next->str);
	}
	return (p_actuel->next);
}


t_tokens	*ft_test_stdin(t_cmd *commande, t_tokens *p_actuel)
{
	int j;

	j = -2;
	if (commande->fd_int_put != -2)
		close(commande->fd_int_put);
	if (p_actuel->next->str != NULL)
	{
		j = access(p_actuel->next->str, F_OK);
		if (j != 0)
			ft_error(1, ": No such file or directory\n", p_actuel->next->str);
		if (j == 0)
		{
			j = access(p_actuel->next->str, X_OK);
			if (j != 0)
				ft_error(1, ": Permission denied\n", p_actuel->next->str);
		}
		if (j == 0)
			commande->fd_int_put = open(p_actuel->next->str, O_RDONLY, 0777);
		if (commande->fd_int_put == -1)
			ft_error(1, ": No such file or directory\n", p_actuel->next->str);
	}
	return (p_actuel->next);
}

t_cmd	*ft_type_token(t_cmd *commande, t_tokens *b_debut)
{
	t_tokens	*p_actuel;
	t_cmd		*a_debut;
	t_cmd		*fin;
	int			i;

	i = 0;
	a_debut = NULL;
	fin = NULL;
	// commande = ft_calloc(sizeof(t_cmd), 1);
	// if (commande == NULL)
	// 	return (NULL);// faire une vrai sorti
	p_actuel = b_debut;
	while (p_actuel)
	{
		if (i == 0 || ft_strncmp(p_actuel->str, "|", 2) == 0)
		{
			commande = ft_creat_token2();
			if (a_debut == NULL)
				a_debut = commande;
			else
				fin->next = commande;
			fin = commande;
			i++;
		}
		if (ft_strncmp(p_actuel->str, ">", 2) == 0 || ft_strncmp(p_actuel->str, ">>", 3) == 0)
			p_actuel = ft_test_stdout(commande, p_actuel);
		else if (ft_strncmp(p_actuel->str, "<", 2) == 0)
			p_actuel = ft_test_stdin(commande, p_actuel);
		else if (ft_strncmp(p_actuel->str, "<<", 3) == 0)
			p_actuel = ft_heredoc_lexer(p_actuel, commande);
		else if (ft_is_str_isprint(p_actuel->str) == 1 && ft_strncmp(p_actuel->str, "|", 2) != 0)
			lexer_cmd(commande, p_actuel);
		p_actuel = p_actuel->next;
	}
	commande = a_debut; 
//	ft_printf_a_debut(a_debut);
	return (commande);
}

int	ft_valid_syntax(t_tokens *token)
{
	t_tokens	*p_actuel;// je peux faire une fonction avec i qui affiche un message different en fonction de i

	p_actuel = token;
	if (ft_strncmp(p_actuel->str, "|", 1) == 0 && p_actuel)
		return (ft_error(1, "syntax error near unexpected token `|'\n", NULL));
	while(p_actuel != NULL)
	{
		if ((p_actuel->next == NULL && ft_strncmp(p_actuel->str, "|", 1) == 0) || ft_strncmp(p_actuel->str, "||", 2) == 0)
			return (ft_error(1, "syntax error near unexpected token '|'\n", NULL));
		else if (ft_strncmp(p_actuel->str, ">>>", 3) == 0 || ft_strncmp(p_actuel->str, "<<<", 3) == 0)
			return (ft_error(1, "syntax error near unexpected token \n", NULL)); // pas exactement le bon message derreur normalement plus precis
		else if (ft_strncmp(p_actuel->str, ">", 1) == 0 || ft_strncmp(p_actuel->str, "<", 1) == 0)
		{
			if (p_actuel->next == NULL || ft_is_str_isprint(p_actuel->next->str) == 0 || ft_strncmp(p_actuel->next->str, ">", 1) == 0 || ft_strncmp(p_actuel->next->str, "<", 1) == 0)
				return (ft_error(1, "syntax error near unexpected token\n", NULL)); // pas exactement le bon message derreur normalement plus precis
		}
		p_actuel = p_actuel->next;
	}
	return (0);
}

void	ft_test_bultins(t_cmd *commande, t_shell *stru)
{
	//pid_t	pid;
	int			status;

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
	stru->last_status = status;
	/* else if (ft_strncmp(commande->cmd, "./", 2) == 0 || ft_strncmp(commande->cmd, "/", 1) == 0 )
	{
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
		{
			execve(commande->cmd, commande->args, &stru->environ->str);
		//	kill(pid, SIGKILL); je pense pas quil soit vraiment necessaire peut etre plus tard quand le programme sera BIG
		}
		else if (pid > 0)
		{
			wait(NULL);
			return ;
		}
	} */// faut faire des gosses sinon on remplace le processus
	//sinon tu fais une fonction qui execute si seulement ls sinon message derreur 
}

void	ft_on_exect(t_cmd *commande, t_shell *stru)
{
	t_cmd	*a_debut;

	a_debut = commande;
	while (a_debut)
	{
		if (commande->cmd != NULL)
			ft_test_bultins(commande, stru); //on peut aussi mettre le exceve
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
	stru->environ = ft_duplicate_env(env);
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
		if (main_variables(stru) == 1)
			continue ;
		main_expand(stru);
		if (stru->tokens != NULL)
		{
			if (ft_valid_syntax(stru->tokens) != -1)
			{
				stru->commande = ft_type_token(stru->commande, stru->tokens);
				// command_expand(stru->commande, stru);
				ft_on_exect(stru->commande, stru);
			}
		}
	}
	//	free_args(stru->tokens->args);
	free_tokens(stru->tokens);
	clear_history();
	//	free_env(*stru->environ);
    return (0);
}



