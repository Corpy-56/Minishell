/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:10:14 by sarah             #+#    #+#             */
/*   Updated: 2025/10/13 12:28:07 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static struct termios orig_termios1;
struct termios saved_term1;

static bool	is_exec_file(const char *chosen_path)
{
	struct stat	info;

	if (!chosen_path)
		return (false);
	if (stat(chosen_path, &info) != 0)
		return (false);
	if (S_ISDIR(info.st_mode))
		return (false);
	if (access(chosen_path, X_OK) != 0)
		return (false);
	return (true);
}

static char	*join_cmd(char *rep, char *name)
{
	char	*tmp;
	char	*base;
	char	*chosen_path;

	if (rep && *rep)
		base = rep;
	else
		base = ".";
	tmp = ft_strjoin(base, "/");
	if (!tmp)
		return (NULL);
	chosen_path = ft_strjoin(tmp, name);
	free(tmp);
	return (chosen_path);
}

char	*find_in_path(char *name, t_shell *stru)
{
	char	**rep;
	char	*chosen_path;
	int		i;

	i = 0;
	if (name == NULL || stru->path_dirs == NULL || ft_strchr(name, '/'))
		return (NULL);
	rep = stru->path_dirs;
	if (rep == NULL)
		return (NULL);
	while (rep[i])
	{
		chosen_path = join_cmd(rep[i], name);
		if (chosen_path && is_exec_file(chosen_path))
			return (chosen_path);
		free(chosen_path);
		i++;
	}
	return (NULL);
}

static char	*exec_external2(char **argv, t_cmd *cmd, t_shell *stru)
{
	struct stat	info;
	char		*path_val;
	char		*chosen_path;

	if (argv == NULL || argv[0] == NULL)
		return (NULL);
	if (ft_strchr(argv[0], '/'))
	{
		if (stat(argv[0], &info) != 0 && cmd->fd_out_put1 == -2 && cmd->fd_out_put2 == -2)
			return (err_msg_file_or_dir(argv, stru), NULL);
		else if (S_ISDIR(info.st_mode))
			return (err_msg_dir(argv, stru), NULL);
		return (argv[0]);
	}
	else
	{
		path_val = get_env_value(stru->environ, "PATH");
		if ((path_val == NULL || path_val[0] == '\0') && cmd->fd_out_put1 == -2 && cmd->fd_out_put2 == -2)
			return (err_msg_file_or_dir(argv, stru), NULL);
		chosen_path = find_in_path(argv[0], stru);
		if (!chosen_path)
			return (err_msg_cmd(argv, stru), NULL);
	}
	return (chosen_path);
}

static void	handle_exec_error(t_ext *ext, t_shell *stru, int error)
{
	free_doublechar(ext->envp);
	if (ext->chosen_path != ext->argv[0])
		free(ext->chosen_path);
	clean_children(stru);
	if (error == ENOENT)
		_exit(127);
	else
		_exit(126);
}

void	exec_external(t_cmd *cmd, t_shell *stru)
{
	t_ext		ext;
	
	init_ext(&ext, cmd);
	if (ext.argv == NULL || ext.argv[0] == NULL)
		return ;
	ext.chosen_path = exec_external2(ext.argv, cmd, stru);
	if (!ext.chosen_path)
		return ;
	ext.envp = env_list_to_envp(stru->environ);
	if (!ext.envp)
	{
		ft_putstr_fd("No envp\n", 2);
		_exit (1);
	}
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	if (execve(ext.chosen_path, ext.argv, ext.envp) == -1)
		handle_exec_error(&ext, stru, errno);
}

// void	exec_external(t_cmd *cmd, t_shell *stru)
// {
// 	struct stat	info;
// 	char		**envp;
// 	int			error;
// 	bool		found_chosen_path;

// 	auto char *path_val, *chosen_path, **argv = cmd->args;
// 	if (argv == NULL || argv[0] == NULL)
// 		return ;
// 	if (ft_strchr(argv[0], '/'))
// 	{
// 		if (stat(argv[0], &info) != 0 && cmd->fd_out_put1 == -2 && cmd->fd_out_put2 == -2)
// 			return (err_msg_file_or_dir(argv, stru));
// 		else if (S_ISDIR(info.st_mode))
// 			return (err_msg_dir(argv, stru));
// 		chosen_path = argv[0];
// 		found_chosen_path = false;
// 	}
// 	else
// 	{
// 		path_val = get_env_value(stru->environ, "PATH");
// 		if ((path_val == NULL || path_val[0] == '\0') && cmd->fd_out_put1 == -2 && cmd->fd_out_put2 == -2)
// 			return (err_msg_file_or_dir(argv, stru));
// 		chosen_path = find_in_path(argv[0], stru);
// 		if (!chosen_path)
// 			return (err_msg_cmd(argv, stru));
// 		else
// 			found_chosen_path = true;
// 	}
// 	envp = env_list_to_envp(stru->environ);
// 	if (!envp)
// 	{
// 		ft_putstr_fd("No envp\n", 2);
// 		exit (1);
// 	}
// 	signal(SIGINT, SIG_DFL);
// 	signal(SIGQUIT, SIG_IGN);
// 	if (execve(chosen_path, argv, envp) == -1)
// 	{
// 		error = errno;
// 		free_doublechar(envp);
// 		if (found_chosen_path)
// 			free(chosen_path);
// 		clean_children(stru);
// 		if (error == ENOENT)
// 			_exit(127);
// 		else if (error == EACCES || error == EISDIR || error == ENOEXEC)
// 			_exit(126);
// 		else
// 			_exit(126);
// 	}
// }

void	disable_echoctl1(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return ;
	orig_termios1 = term;
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	save_termios1(void)
{
	tcgetattr(STDIN_FILENO, &saved_term1);
}
void	restore_termios1(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &saved_term1);
}

static int	collect_status(pid_t pid, t_shell *stru)
{
	int	status;

	(void)stru;
	status = 0;
	waitpid(pid, &status, 0);
	// restore_termios1();
	// stru->last_status = extract_exit_status(status);
	return (status);
}

static void	run_child(t_cmd *cmd, t_shell *stru, int f)
{
	(void)f;	
	disable_echoctl1();
	signal(SIGQUIT, SIG_IGN);
//	f = ft_first_ft_redirections(cmd, f, stru);
//	if (f == -1)
//			exit(0) ;
	if (cmd->heredoc != NULL)
	{
		dup2(f, STDIN_FILENO);
		close(f);
	}
	exec_external(cmd, stru);
	clean_children(stru);
	_exit(stru->last_status);
}

int	run_external(t_cmd *cmd, t_shell *stru, int f)
{
	int		pid;
	int		status;

	(void)f;
	(void)stru;
	status = 0;
	if (cmd->args[0] == NULL)
		return (0);
	signal(SIGINT, SIG_IGN);// il est ultra important 
	// signal(SIGQUIT, SIG_IGN);
	save_termios1();
	pid = fork();
	if (pid < 0)
		return (stru->last_status = 1);
	if (pid == 0)
		run_child(cmd, stru, f);
	status = collect_status(pid, stru);
	restore_termios1();
	ft_signal();
	return (status);
}

// int	run_external(t_cmd *cmd, t_shell *stru, int f)
// {
// 	int		pid;
// 	int		status;

// 	(void)f;
// 	if (cmd->args[0] == NULL)
// 		return (0);
// 	signal(SIGINT, SIG_IGN);// il est ultra important 
// 	//signal(SIGQUIT, SIG_IGN);
// 	save_termios1();
// 	pid = fork();
// 	if (pid < 0)
// 	{
// 		stru->last_status = 1;
// 		return (0);
// 	}
// 	if (pid == 0)
// 	{
// 		disable_echoctl1();
// 		signal(SIGQUIT, SIG_IGN);
// 	//	f = ft_first_ft_redirections(cmd, f, stru);
// 	//	if (f == -1)
// 	//			exit(0) ;
// 		if (cmd->heredoc != NULL)
// 		{
// 			dup2(f, STDIN_FILENO);
// 			close(f);
// 		}
// 		exec_external(cmd, stru);
// 		status = stru->last_status;
// 		clean_children(stru);
// 		_exit(status);
// 	}
// 	else
// 	{
// 		//restore_termios1();
// 		//signal(SIGQUIT, SIG_IGN);
// 		status = 0;
// 		waitpid(pid, &status, 0);
// 		restore_termios1();
// 		// stru->last_status = extract_exit_status(status);
// 		return (status);
// 	}
// 	return (0);
// }

