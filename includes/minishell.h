/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:56:57 by skuor             #+#    #+#             */
/*   Updated: 2025/08/05 16:52:40 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "tokenisation.h"
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>

//builtins
int			ft_exit(char **args);
int			ft_pwd(char **args);
int			ft_env(t_shell *stru, char **env);
int			ft_echo(char **args);
int			ft_cd(char **args);
int			ft_unset(t_shell *stru, char **args);

int	check_valid_var(char *str);

//main
int			main(int argc, char **argv, char **env);

//utils
int			ft_error(int i, char *str, char *str2);
int			white_space(char *str, int i);
void		free_args(char **args);
void		free_tokens(t_tokens *token);

//tokenisation
char		*ft_strjoin_char(char *str, const char c);
void		ft_quote(char *rl, int i);
int			count_tokens(t_tokens *token);
char		*ft_tokenisation_quote(char *rl, char *temp, int i);
char		**args_from_tokens(t_tokens *token);
t_tokens	*ft_creat_token(char *temp);
t_tokens	*ft_tokenisation(char *rl, t_tokens *token);

//environ
t_env		*ft_duplicate_env(char **env);

//variables
t_tokens	expand_var(t_tokens *token, int exit_status);


#endif