/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:42:44 by skuor             #+#    #+#             */
/*   Updated: 2025/08/13 18:39:34 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENISATION_H
# define TOKENISATION_H

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	int				fd_out_put1;
	int				fd_out_put2;
	int				fd_int_put;
	char			*heredoc;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_env
{
	char			*str; //KEY=value
	int				i;
	char			*name;
	char			*value;
	int				exported;
	struct s_env	*next;
}					t_env;

typedef struct s_tokens
{
	char			*str;
	char			**args;
	int				type_i;
	struct s_tokens	*next;	
}					t_tokens;

typedef struct s_shell
{
	t_cmd		*commande;
	t_tokens	*tokens;
	t_env		*environ;
}				t_shell;

#endif