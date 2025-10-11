/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:42:44 by skuor             #+#    #+#             */
/*   Updated: 2025/10/11 11:43:26 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENISATION_H
# define TOKENISATION_H

typedef struct s_redir
{
	int				type;
	char			*target;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	int				fd_out_put1;
	int				fd_out_put2;
	int				fd_int_put;
	char			**heredoc;
	t_redir			*redirs;
	int				is_builtin;
	int				here;
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

typedef struct s_fd
{
	int				fd;
	int				fd_out;
	int				fd_in;
	int				fd_out_put1;
	int				fd_out_put2;
	int				fd_int_put;
}					t_fd;

extern t_fd *fd;

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
}					t_pipes;

typedef struct s_path
{
	char			**rep;
	char			*base;
	char			*chosen_path;
	char			*tmp;
	struct stat		info;
	int				i;
}					t_path;

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
}					t_cd;

typedef struct s_shell
{
	t_cmd			*commande;
	t_tokens		*tokens;
	t_env			*environ;
	t_env			*local;
	t_env			*path_node;
	char			**path_dirs;
	int				last_status;
	int				should_exit;
}					t_shell;

#endif