/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:56:23 by agouin            #+#    #+#             */
/*   Updated: 2025/10/18 13:01:22 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*ft_test_stdout(t_cmd *cmd, t_tokens *p_temp, t_shell *stru)
{
	t_tokens	*p_a;

	p_a = p_temp;
	if (ft_strncmp(p_a->str, ">", 2) == 0)
	{
		if (cmd->fd_out_put1 >= 0)
			close_fds(&cmd->fd_out_put1);
		if (p_a->next->str != NULL)
			cmd->fd_out_put1 = open(p_a->next->str,
					O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (cmd->fd_out_put1 == -1)
			ft_error(1, ": Permission denied\n", p_a->next->str, stru);
	}
	else if (ft_strncmp(p_a->str, ">>", 3) == 0)
	{
		if (cmd->fd_out_put2 >= 0)
			close_fds(&cmd->fd_out_put2);
		if (p_a->next->str != NULL)
			cmd->fd_out_put2 = open(p_a->next->str, O_CREAT
					| O_WRONLY | O_APPEND, 0644);
		if (cmd->fd_out_put2 == -1)
			ft_error(1, ": Permission denied\n", p_a->next->str, stru);
	}
	return (p_temp->next);
}

t_tokens	*ft_test_stdin(t_cmd *commande, t_tokens *p_actuel, t_shell *stru)
{
	int	j;

	j = -2;
	if (commande->fd_int_put >= 0)
		close(commande->fd_int_put);
	if (p_actuel->next->str != NULL)
	{
		j = access(p_actuel->next->str, F_OK);
		if (j != 0)
		{
			ft_error(1, ": No such file or directory\n",
				p_actuel->next->str, stru);
			commande->fd_int_put = -1;
			return (p_actuel->next);
		}
		if (j == 0)
			commande->fd_int_put = open(p_actuel->next->str, O_RDONLY, 0777);
		if (commande->fd_int_put == -1)
			ft_error(1, ": Permission denied\n", p_actuel->next->str, stru);
	}
	return (p_actuel->next);
}

t_tokens	*ft_heredoc_lexer(t_tokens *p_actuel, t_cmd *commande)
{
	int			i;
	t_tokens	*a_debut;

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
		while (commande->heredoc[i] != NULL)
			i++;
		if (a_debut->next->str != NULL)
			commande->heredoc[i] = ft_strdup(a_debut->next->str);
	}
	return (p_actuel->next);
}

t_tokens	*ft_type_token_2(t_tokens *p_actuel, t_cmd *comm, t_shell *stru)
{
	if (ft_strncmp(p_actuel->str, ">", 1) == 0)
		p_actuel = ft_test_stdout(comm, p_actuel, stru);
	else if (ft_strncmp(p_actuel->str, "<", 2) == 0)
		p_actuel = ft_test_stdin(comm, p_actuel, stru);
	else if (ft_strncmp(p_actuel->str, "<<", 3) == 0)
		p_actuel = ft_heredoc_lexer(p_actuel, comm);
	else if (ft_is_str_isprint(p_actuel->str) == 1
		&& ft_strncmp(p_actuel->str, "|", 2) != 0)
	{
		if (comm->cmd == NULL && is_assignment_word(p_actuel->str))
			stru->local = create_local_var(p_actuel->str, stru->local, stru);
		else
			lexer_cmd(comm, p_actuel, 0, 0);
	}
	return (p_actuel);
}

t_cmd	*ft_type_token(t_cmd *commande, t_tokens *b_debut, t_shell *stru)
{
	t_type	t;

	init_type(&t, b_debut);
	while (t.p_actuel)
	{
		if (t.i == 0 || ft_strncmp(t.p_actuel->str, "|", 2) == 0)
		{
			commande = ft_creat_token2();
			if (t.a_debut == NULL)
				t.a_debut = commande;
			else
				t.fin->next = commande;
			t.fin = commande;
			t.i++;
		}
		t.p_actuel = ft_type_token_2(t.p_actuel, commande, stru);
		t.p_actuel = t.p_actuel->next;
	}
	commande = t.a_debut;
	commande = ft_test_no_errors(commande);
	return (commande);
}
