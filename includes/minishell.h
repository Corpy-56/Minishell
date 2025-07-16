/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:56:57 by skuor             #+#    #+#             */
/*   Updated: 2025/07/16 16:17:04 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "tokenisation.h"
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

//builtins
int			ft_exit(char **args);
int			ft_pwd(char **args);
int			ft_env(t_shell *stru);
int			ft_echo(char **args);
int			ft_cd(char **args);

//main
int			main(int argc, char **argv, char **env);

//utils
int			ft_error(int i, char *str);
int			white_space(char *str, int i);
void		free_args(char **args);
void		free_tokens(t_tokens *token);

//tokenisation
int			count_tokens(t_tokens *token);
char		**args_from_tokens(t_tokens *token);
t_tokens	*ft_tokenisation(char *rl, t_tokens *token);

//environ
t_env		*ft_duplicate_env(char **env);


#endif