/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:56:57 by skuor             #+#    #+#             */
/*   Updated: 2025/08/14 19:02:39 by skuor            ###   ########.fr       */
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
int			ft_env(t_shell *stru);
//int		ft_env(t_shell *stru, char **env);
int			ft_echo(char **args);
int			ft_cd(char **args);
int			ft_unset(t_shell *stru, char **args);
//int			ft_export(char **args);
int	ft_export(char **args, t_env *env, t_env *local);


//main
int			main(int argc, char **argv, char **env);

//utils
int			ft_error(int i, char *str, char *str2);
int			white_space(char *str, int i);
void		free_args(char **args);
void		free_tokens(t_tokens *token);
bool		is_assignement(char *str);


//utils_var
void		parse_args(char *args, char **name, char **value);
int			check_valid_var(char *str);
void 		update_local_value(t_env *local, char *name, char *new_value);

void		update_value(t_env *var, char *new_value);
t_env		*find_var(t_env *env, char *name);
void		mark_exported(t_env *var);



//tokenisation
int			count_tokens(t_tokens *token);
char		**args_from_tokens(t_tokens *token);
t_tokens	*ft_tokenisation(char *rl, t_tokens *token);

//environ
t_env		*ft_duplicate_env(char **env);

//variables
t_env		*add_to_list(t_env *local, char *name, char *value);
t_env		*create_local_var(char **args, t_env *local);
char		*expand_var(char *args, t_env *env, t_env *local);
void		move_var_to_env(t_env **env, t_env **local, t_env *var);





#endif

