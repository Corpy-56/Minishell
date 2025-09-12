/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:56:57 by skuor             #+#    #+#             */
/*   Updated: 2025/09/12 13:27:02 by skuor            ###   ########.fr       */
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
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>

//builtins
int			ft_cd(char **args);
int			ft_echo(char **args);
int			ft_env(t_env *env);
int			ft_exit(char **args);
int			ft_export(char **args, t_env **env, t_env **local);
int			ft_pwd(char **args);
int			ft_unset(t_shell *stru, char **args);

//main
int			main(int argc, char **argv, char **env);

//tokenisation
int			count_tokens(t_tokens *token);
char		**args_from_tokens(t_tokens *token);
t_tokens	*ft_tokenisation(char *rl, t_tokens *token);

//environ
t_env		*ft_duplicate_env(char **env, t_shell *stru);
// t_env		*ft_duplicate_env(char **env);
t_env		*create_env_node(char *str);

//variables
t_env		*add_to_local(t_env *local, char *name, char *value);
t_env		*create_local_var(char *args, t_env *local);
void		move_var_to_env(t_env **env, t_env **local, t_env *var);
int			main_variables(t_shell *stru);

//expansion
// char		*expand_var(char *args, t_shell *stru);
char		*expand_var(t_tokens *token, t_shell *stru, size_t i);
void		main_expand(t_shell *stru);

//token_type
t_cmd		*ft_type_token(t_cmd *commande, t_tokens *b_debut);
t_tokens	*ft_type_token_2(t_tokens *p_actuel, t_cmd *commande);
t_tokens	*ft_test_stdout(t_cmd *cmd, t_tokens *p_temp);
t_tokens	*ft_test_stdin(t_cmd *commande, t_tokens *p_actuel);
t_tokens	*ft_heredoc_lexer(t_tokens *p_actuel, t_cmd *commande);

//external_commands
void		run_external(t_cmd *cmd, t_shell *stru, char **env);

//utils
int			ft_error(int i, char *str, char *str2);
int			white_space(char *str, int i);
bool		is_local_var(char *str);

//utils_var
int			check_valid_var(char *str);
t_env		*find_var(t_env *env, char *name);
void		parse_args(char *args, char **name, char **value);
void		update_value(t_env *var, char *new_value);
void		update_str(t_env *var);

//utils_expan
char		*get_env_value(t_env *env, char *name);
int			is_assignment_word(const char *str);
void		command_expand(t_cmd *cmd, t_shell *stru);

//utils_token
int			count_tokens(t_tokens *token);
char		**args_from_tokens(t_tokens *token);
int			count_tokens(t_tokens *token);
// t_tokens	*ft_creat_token(char *temp);
void		ft_quote(char *rl, int i);
char		*ft_strjoin_char(char *str, const char c);
t_tokens	*ft_creat_token(char *rl, int i);

//free
void		free_args(char **args);
void		free_tokens(t_tokens *token);
void		free_env(char **env);

//token_type_utils
void		ft_initialization_commande(t_cmd *commande);
t_cmd		*ft_creat_token2(void);
t_cmd		*lexer_cmd(t_cmd *commande, t_tokens *p_actuel);
int			ft_nb_tokens(t_tokens *p_actuel);
int			ft_valid_syntax(t_tokens *token);

#endif

