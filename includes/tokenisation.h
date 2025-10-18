/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:42:44 by skuor             #+#    #+#             */
/*   Updated: 2025/10/18 11:13:34 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENISATION_H
# define TOKENISATION_H

# include <signal.h>
# include <termios.h>

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	int				fd_out_put1;
	int				fd_out_put2;
	int				fd_int_put;
	char			**heredoc;
	int				is_builtin;
	int				here;
	int				fd_dup_0;
	int				fd_dup_1;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_env
{
	char			*str;
	int				i;
	char			*name;
	char			*value;
	char			**path;
	struct s_env	*next;
}					t_env;

typedef struct s_tokens
{
	char			*str;
	char			**args;
	int				dollars;
	int				type_i;
	struct s_tokens	*next;	
}					t_tokens;

typedef struct s_split
{
	const char		*ifs;
	const char		*str;
	char			**fields;
	char			*new_field;
	size_t			i;
	size_t			j;
	size_t			n_fields;
	size_t			start;
	t_tokens		*prev;
	t_tokens		*current;
	t_tokens		*last;
}					t_split;

typedef struct s_fd_opens_childs
{
	int				fd_here;
	int				fd_int;
	int				fd_out1;
	int				fd_out2;
}					t_fd_opens;

typedef struct s_pipes
{
	int				fd[2];
	int				i;
	int				n;
	int				prev_read;
	int				status;
	int				last_status;
	int				builtins;
	t_cmd			*current;
	pid_t			wait_child;
	pid_t			pid;
	pid_t			last_pid;
	t_fd_opens		f;
}					t_pipes;

typedef struct s_copy
{
	char			*new_val;
	char			*new_str;
	size_t			name_len;
	size_t			val_len;
}					t_copy;

typedef struct s_tab
{
	char			**envp;
	char			*line;
	int				n_nodes;
	size_t			i;
	t_env			*node;
}					t_tab;

typedef struct s_exec
{
	t_cmd			*head;
	int				builtins;
	int				n;
	int				fd_stdin;
	int				fd_stdout;
	int				fd;
	int				status;
}					t_exec;

typedef struct s_cd
{
	char			*home;
	char			*pwd;
	char			*oldpwd;
	char			*newpwd;
	char			*old;
}					t_cd;

typedef struct s_ext
{
	char			**envp;
	char			**argv;
	int				error;
	char			*path_val;
	char			*chosen_path;
}					t_ext;

typedef struct s_expand
{
	char			*str;
	char			*out;
	size_t			len_str;
	size_t			start;
	size_t			j;
}					t_expand;

typedef struct s_export
{
	int				i;
	char			*name;
	char			*value;
	t_env			*var;
	char			*val_final;
	t_env			**env;
	t_env			**local;
}					t_export;

typedef struct s_unset
{
	t_env			*prev;
	t_env			*node;
	t_env			*next;
	int				size_var;
}					t_unset;

typedef struct s_type
{
	t_tokens		*p_actuel;
	t_cmd			*a_debut;
	t_cmd			*fin;
	int				i;
}					t_type;

typedef struct s_dupenv
{
	int				i;
	t_env			*fin;
	t_env			*a_debut;
	t_env			*new;
}					t_dupenv;

typedef struct s_quote
{
	int				quote1;
	char			q;
}					t_quote;

typedef struct s_shell
{
	t_cmd			*commande;
	t_tokens		*tokens;
	t_env			*environ;
	t_env			*local;
	t_env			*path_node;
	t_exec			*exec;
	char			**path_dirs;
	int				last_status;
	int				should_exit;
	int				hdc_interrupted;
	int				dup_0;
	int				dup_1;
	int				fd;
	int				status;
}					t_shell;

#endif