/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:56:57 by skuor             #+#    #+#             */
/*   Updated: 2025/10/15 19:46:27 by skuor            ###   ########.fr       */
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
# include <termios.h>

# define MINISHELL "\001\033[1;32m\002Minishell : \001\033[0m\002"

/* ******************************** BUILTINS ******************************** */

/* ********* builtins ********* */
int			ft_cd(char **args, t_shell *stru);
int			ft_echo(char **args);
int			ft_env(t_env *env);
int			ft_exit(t_shell *stru, char **args, bool cmd_seule);
int			ft_export(char **args, t_env **env, t_env **local, t_shell *stru);
int			ft_pwd(char **args, t_shell *stru);
int			ft_unset(t_shell *stru, char **args);

/* ********* exit - 2 - ********* */
int			str_to_long(const char *str, long *out);
void		print_exit(bool cmd_seule);

/* ******************************** SOURCES ******************************** */

/* ********* tokenisation ********* */
char		*ft_one_token_extra(char *rl, int i, t_tokens *token);
int			ft_token_redirection(char *rl, int i, t_tokens *token);
int			ft_one_token(char *rl, int i, t_tokens *token);
t_tokens	*ft_tokenisation(char *rl, t_tokens *token, int i);

/* ********* environ ********* */
t_env		*ft_duplicate_env(char **env, t_shell *stru);
t_env		*create_env_node(char *str);
int			update_env(t_env *head, char *name, char *value, t_shell *stru);
void		update_shlvl(t_env *env, t_shell *stru);
char		**env_list_to_envp(t_env *env);

/* ********* variables ********* */
t_env		*add_to_local(t_env *local, char *name, char *value);
t_env		*create_local_var(char *args, t_env *local, t_shell *stru);
void		move_var_to_env(t_env **env, t_env **local, t_env *var);
int			main_variables(t_shell *stru);

/* ********* expansion ********* */
char		*expand_var(t_tokens *token, t_shell *stru, size_t i);
size_t		expand_var2(t_shell *stru, char *args, size_t i, char **str);
void		main_expand(t_shell *stru);

/* ********* token_type ********* */
t_cmd		*ft_type_token(t_cmd *commande, t_tokens *b_debut, t_shell *stru);
t_tokens	*ft_type_token_2(t_tokens *p_actuel, t_cmd *cmd, t_shell *stru);
t_tokens	*ft_test_stdout(t_cmd *cmd, t_tokens *p_temp);
t_tokens	*ft_test_stdin(t_cmd *commande, t_tokens *p_actuel);
t_tokens	*ft_heredoc_lexer(t_tokens *p_actuel, t_cmd *commande);

/* ********* extenal cmds ********* */
char		*find_in_path(char *name, t_shell *stru);
char		*exec_external2(char **argv, t_cmd *cmd, t_shell *stru);
void		handle_exec_error(t_ext *ext, t_shell *stru, int error);
void		exec_external(t_cmd *cmd, t_shell *stru);
int			collect_status(pid_t pid, t_shell *stru);
int			run_external(t_cmd *cmd, t_shell *stru, int f);
void		save_termios1(void);
void		restore_termios1(void);

/* ********* exec ********* */
int			count_maillons(t_cmd *cmd);
void		exec_cmd_line(t_shell *stru);
t_cmd		*ft_test_heredoc_pipes(t_cmd *cmds, t_shell *sh);
void		ft_first_ft_redirections2(t_cmd *head);

/* ********* ft_heredocs ********* */
int			ft_setup_heredoc(t_cmd *commande, t_shell *stru);
void		ft_child_heredoc(t_cmd *commande, t_shell *stru, int j, int pidfd);
int			ft_heredoc(t_cmd *commande, int pidfd, int i, char *line);
void		signal_handler(int signum, siginfo_t *info, void *context);

/* ********* ft_signals ********* */
void		ft_signal(void);
void		signal_handler1(int signum);
void		set_shell(t_shell *shell);
void		ft_ignore_signal(void);

/* ********* hide signals ********* */
void		restore_termios(void);
void		save_termios(void);
void		disable_echoctl(void);

/* ********* fields_splitting ********* */
size_t		count_fields(const char *str, const char *ifs);
void		split_all_tokens(t_tokens **head, t_shell *stru);

/* ********* pipes ********* */
void		run_pipes(t_cmd *head, t_shell *sh);

/* ********* main ********* */
int			main(int argc, char **argv, char **env);
void		ft_tty(t_shell *stru);

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
int			update_value(t_env *var, char *new_value);

/* ********* utils_expan ********* */
char		*get_env_value(t_env *env, char *name);
int			is_assignment_word(const char *str);
bool		is_ifs(char c, const char *ifs);
int			extract_exit_status(int status);
size_t		i_equal_start(char **str, size_t *start);

/* ********* utils_token ********* */
int			ft_quote(char *rl, int i);
char		*ft_strjoin_char(char *str, const char c);
int			white_space(char *str, int i);
int			count_nodes(t_env *list);
char		*join_cmd(char *rep, char *name);

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
int			ft_exec_builtins(t_cmd *commande, t_shell *stru, bool cmd_seule);

/* ********* utils_cmd ********* */
t_cmd		*suppr_empty_cmd(t_cmd *head);
t_tokens	*ft_creat_token(char *rl, int i);
t_cmd		*ft_test_no_errors(t_cmd *commande);

/* ********* utils exect redirections ********* */
char		*ft_end_expand(size_t start, char *str, char *line, size_t i);
char		*ft_expand_heredoc2(char *l, t_shell *sh, size_t i, size_t start);
int			ft_expand_heredoc(int fd, t_shell *stru, int new_fd);
int			ft_first_ft_redirections(t_cmd *head, int fd, t_shell *stru);
void		ft_close_fd(t_cmd *head, int fd_stdin, int fd_stdout, int fd);
void		apply_cmd_redirs_in_child(t_cmd *cmd, t_shell *stru);

/* ********* utils pipes ********* */
void		ignore_sigpipe_once(void);
void		bad_fork(t_pipes *pipes, t_shell *sh);
char		*join_three_char(char *a, char *b, char *c);
t_shell		*static_struct(t_shell *stru);
bool		is_exec_file(const char *chosen_path);

/* ********* utils fields split ********* */
char		**split_by_ifs(const char *str, const char *ifs);

/* ********* free ********* */
void		free_tokens(t_tokens *token);
void		free_env(t_env **env);
void		free_cmds(t_cmd *cmd);
void		free_doublechar(char **to_free);
void		free_fields(char **fields, size_t i);
char		*ft_free_str(char *str);

/* ********* clean ********* */
void		clean_cmd(t_shell *stru);
void		clean_all(t_shell *stru);
void		clean_children(t_shell *stru);
void		clean_gnl(void);
void		clean_heredoc(t_shell *stru);
void		clean_env(t_shell *stru);

/* ********* error msg ********* */
void		err_msg_cmd(char **argv, t_shell *stru);
void		err_msg_export(char *argv);
void		err_msg_syntax(char *c);
void		err_msg_dir(char **argv, t_shell *stru);
void		err_msg_chdir(char **args);
void		err_msg_file_or_dir(char **argv, t_shell *stru);
void		err_msg_cd(char *args);
void		err_msg_num(char **argv, t_shell *stru);
void		err_msg_ambiguous(char *args);

/* ********* init ********* */
void		ft_initialization_commande(t_cmd *commande);
void		ft_init_fd1(void);
void		init_split(t_split *split, t_tokens **head, t_shell *stru);
void		init_split_ifs(t_split *split, const char *str, const char *ifs);
void		init_pipes(t_pipes *pipes, t_cmd *head);
void		init_copy(t_copy *copy, t_env *var, char *new_value);
void		init_tab(t_tab *tab, t_env *env);
void		init_exec(t_exec *exec, t_shell *stru);
void		init_cd(t_cd *cd, t_shell *stru);
void		init_ext(t_ext *ext, t_cmd *cmd);
void		init_expand(t_expand *exp, t_tokens *tk, size_t i);
void		init_shell(t_shell *stru, char **env);
void		init_export(t_export *exp, t_env **env, t_env **local);

/* ********* utils tokenisations ********* */
void		ft_test_minishell(t_tokens *a_debut);
int			ft_init_tokenisation(char *rl, int i);

void		close_fds(int *fd);
void minishell_exit(t_shell *s, t_exec *e, int status);


#endif
