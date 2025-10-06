/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:10:14 by sarah             #+#    #+#             */
/*   Updated: 2025/10/06 18:32:47 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_in_path(char *name, t_shell *stru)
{
	char	**rep;
	char	*base;
	char	*chosen_path;
	char	*tmp;
	struct stat	info;
	int		i;

	i = 0;
	if (name == NULL || stru->path_dirs == NULL)
		return (NULL);
	while (name[i])
	{
		if (name[i] == '/')
			return (NULL);
		i++;
	}
	i = 0;
	rep = stru->path_dirs;
	if (rep == NULL)
		return (NULL);
	while (rep[i])
	{
		if (rep[i][0] == '\0')
			base = ".";
		else
			base = rep[i];
		tmp = ft_strjoin(base, "/");
		chosen_path = ft_strjoin(tmp, name);
		free(tmp);
		if (!chosen_path)
		{
			i++;
			continue ;
		}
		if (stat (chosen_path, &info) != 0)
		{
			free(chosen_path);
			i++;
			continue ;
		}
		if (S_ISDIR(info.st_mode) != 0)
		{
			free(chosen_path);
			i++;
			continue ;
		}
		if (access(chosen_path, X_OK) != 0)
		{
			free(chosen_path);
			i++;
			continue ;
		}
		// printf("%s\n", chosen_path);
		return (chosen_path);
	}
	return (NULL);
}

void	exec_external(t_cmd *cmd, t_shell *stru)
{
	struct stat	info;
	char		**envp;
	int			error;
	bool		found_chosen_path;

	auto char *path_val, *chosen_path, **argv = cmd->args;
	if (argv == NULL || argv[0] == NULL)
		return ;
	if (ft_strchr(argv[0], '/'))
	{
		if (stat(argv[0], &info) != 0)
			return (err_msg_file_or_dir(argv, stru));
		else if (S_ISDIR(info.st_mode))
			return (err_msg_dir(argv, stru));
		chosen_path = argv[0];
		found_chosen_path = false;
	}
	else
	{
		path_val = get_env_value(stru->environ, "PATH");
		if (path_val == NULL || path_val[0] == '\0')
			return (err_msg_file_or_dir(argv, stru));
		chosen_path = find_in_path(argv[0], stru);
		if (!chosen_path)
			return (err_msg_cmd(argv, stru));
		else
			found_chosen_path = true;
	}
	envp = env_list_to_envp(stru->environ);
	if (!envp)
	{
		ft_putstr_fd("No envp\n", 2);
		exit (1);
	}
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (execve(chosen_path, argv, envp) == -1)
	{
		error = errno;
		free_doublechar(envp);
		if (found_chosen_path)
			free(chosen_path);
		if (error == ENOENT)
			_exit(127);
		if (error == EACCES || error == EISDIR || error == ENOEXEC)
			_exit(126);
	}
	exit(stru->last_status);
}

void	run_external(t_cmd *cmd, t_shell *stru, int fd)
{
	int		pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		stru->last_status = 1;
		return ;
	}
	if (pid == 0)
	{
		if (cmd->heredoc != NULL)
		{
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		exec_external(cmd, stru);
		exit(stru->last_status);
	}
	else
	{
		status = 0;
		waitpid(pid, &status, 0);
		stru->last_status = extract_exit_status(status);
	}
}