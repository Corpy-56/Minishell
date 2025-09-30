/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:56:57 by skuor             #+#    #+#             */
/*   Updated: 2025/09/30 15:29:23 by skuor            ###   ########.fr       */
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
# include <errno.h>

/* ******************************** BUILTINS ******************************** */

/* ********* builtins ********* */
int			ft_cd(char **args, t_shell *stru);
int			ft_echo(char **args);
int			ft_env(t_env *env);
int			ft_exit(t_shell *stru, char **args);
int			ft_export(char **args, t_env **env, t_env **local);
int			ft_pwd(char **args, t_shell *stru);
int			ft_unset(t_shell *stru, char **args);

/* ******************************** SOURCES ******************************** */

/* ********* tokenisation ********* */
int			count_tokens(t_tokens *token);
char		**args_from_tokens(t_tokens *token);
t_tokens	*ft_tokenisation(char *rl, t_tokens *token);

/* ********* environ ********* */
t_env		*ft_duplicate_env(char **env, t_shell *stru);
t_env		*create_env_node(char *str);
int			update_env(t_env *head, char *name, char *value, t_shell *stru);


/* ********* variables ********* */
t_env		*add_to_local(t_env *local, char *name, char *value);
t_env		*create_local_var(char *args, t_env *local, t_shell *stru);
void		move_var_to_env(t_env **env, t_env **local, t_env *var);
int			main_variables(t_shell *stru);

/* ********* expansion ********* */
char		*expand_var(t_tokens *token, t_shell *stru, size_t i);
size_t		expand_var2(t_shell *stru, char *args, size_t i, char **str);
void		main_expand(t_shell *stru);
void		split_all_tokens(t_tokens *head, t_shell *stru);

/* ********* token_type ********* */
t_cmd		*ft_type_token(t_cmd *commande, t_tokens *b_debut, t_shell *stru);
t_tokens	*ft_type_token_2(t_tokens *p_actuel, t_cmd *cmd, t_shell *stru);
t_tokens	*ft_test_stdout(t_cmd *cmd, t_tokens *p_temp);
t_tokens	*ft_test_stdin(t_cmd *commande, t_tokens *p_actuel);
t_tokens	*ft_heredoc_lexer(t_tokens *p_actuel, t_cmd *commande);

/* ********* extenal cmds ********* */
void		exec_external(t_cmd *cmd, t_shell *stru, char **env);
void		run_external(t_cmd *cmd, t_shell *stru, char **env);

/* ********* exec ********* */
void		exec_cmd_line(t_shell *stru, char **env);

/* ********* ft_heredocs ********* */
int			ft_setup_heredoc(t_cmd *commande);
void		ft_child_heredoc(t_cmd *commande);
void		ft_heredoc(t_cmd *commande, int pidfd, int i);
void		signal_handler(int signum, siginfo_t *info, void *context);

/* ********* ft_signals ********* */
void		ft_signal(void);
void		signal_handler1(int signum);
void		ft_exit_d(void);

/* ********* fields_splitting ********* */
size_t		count_fields(const char *str, const char *ifs);
char		**split_by_ifs(const char *str, const char *ifs);
void		split_all_tokens(t_tokens *head, t_shell *stru);


/* ********* main ********* */
int			main(int argc, char **argv, char **env);

/* ******************************** UTILS ********************************** */

/* ********* utils ********* */
int			ft_error(int i, char *str, char *str2);
bool		is_operator(char *op);
bool		is_local_var(char *str);
int			append_char(char **result, char c);
int			append_str(char **result, const char *str);

/* ********* utils_var ********* */
int			check_valid_var(char *str);
t_env		*find_var(t_env *env, char *name);
void		parse_args(char *args, char **name, char **value);
void		update_value(t_env *var, char *new_value);
void		update_str(t_env *var);

/* ********* utils_expan ********* */
char		*get_env_value(t_env *env, char *name);
int			is_assignment_word(const char *str);
bool		is_ifs(char c, const char *ifs);
int			extract_exit_status(int status);
char		**split_by_ifs(const char *str, const char *ifs);

/* ********* utils_token ********* */
int			count_tokens(t_tokens *token);
char		**args_from_tokens(t_tokens *token);
void		ft_quote(char *rl, int i);
char		*ft_strjoin_char(char *str, const char c);
int			white_space(char *str, int i);

/* ********* utils_quotes ********* */
bool		is_quote(char quote);
void		skip_quoted(const char *str, size_t *i);
char		*remove_quotes(const char *str);
void		unquote_tokens(t_tokens *head);

/* ********* type_toke_utils ********* */
void		ft_initialization_commande(t_cmd *commande);
t_cmd		*ft_creat_token2(void);
t_cmd		*lexer_cmd(t_cmd *commande, t_tokens *p_actuel);
int			ft_nb_tokens(t_tokens *p_actuel);
int			ft_valid_syntax(t_tokens *token);

/* ********* utils_builtins ********* */
bool		is_builtin(t_cmd *commande);
int			ft_test_bultins(t_cmd *commande, t_shell *stru);

/* ********* utils_cmd ********* */
t_cmd		*suppr_empty_cmd(t_cmd *head);

/* ********* free ********* */
void		free_tokens(t_tokens *token);
void		free_env(t_env **env);
void		free_cmds(t_cmd *cmd);
void		free_doublechar(char **to_free);
void		free_fields(char **fields, size_t i);

/* ********* clean ********* */
void		clean_cmd(t_shell *stru);
void		clean_all(t_shell *stru);

/* ********* error msg ********* */
void		err_msg_cmd(char **argv, t_shell *stru);
void		err_msg_export(char *argv);
void		err_msg_syntax(char *c);
void		err_msg_dir(char **argv, t_shell *stru);
void		err_msg_chdir(char **args);

#endif

