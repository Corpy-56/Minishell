/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:10:14 by sarah             #+#    #+#             */
/*   Updated: 2025/09/19 14:41:19 by skuor            ###   ########.fr       */
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

void	exec_external(t_cmd *cmd, t_shell *stru, char **env)
{

	auto char *path_val, *chosen_path, **argv = cmd->args;
	if (argv == NULL || argv[0] == NULL)
		return ;
	if (ft_strchr(argv[0], '/'))
		execve(argv[0], argv, env);
	path_val = get_env_value(stru->environ, "PATH");
	if (path_val == NULL)
		err_msg_cmd(argv);
	chosen_path = find_in_path(argv[0], stru);
	if (chosen_path)
		execve(chosen_path, argv, env);
	else
		err_msg_cmd(argv);
}

void	run_external(t_cmd *cmd, t_shell *stru, char **env)
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
		exec_external(cmd, stru, env);
	else
	{
		status = 0;
		waitpid(pid, &status, 0);
		stru->last_status = extract_exit_status(status);
	}
}
