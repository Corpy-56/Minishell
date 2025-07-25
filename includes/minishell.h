/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:34:20 by agouin            #+#    #+#             */
/*   Updated: 2025/07/25 16:00:56 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	int				fd_out_put1;
	int				fd_out_put2;
	int				fd_int_put;
	char			*heredoc;
	struct s_cmd	*next;
}t_cmd;

typedef struct s_env
{
	char			*str;
	int				i;
	struct s_env	*next;
}t_env;

typedef struct s_tokens
{
	char			*str;
	struct s_tokens	*next;	
}t_tokens;

typedef struct s_shell
{
	t_cmd		*commande;
	t_tokens	*tokens;
	t_env		*environ;
}t_shell;

t_env		*ft_duplicate_env(char **env);
t_tokens	*ft_tokenisation(char *rl, t_tokens *token);
int			white_space(char *str, int i);
int			ft_error(int i, char *str, char *str2);
char		*ft_strjoin_char(char *str, const char c);

#endif
