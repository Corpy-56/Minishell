/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:10:14 by sarah             #+#    #+#             */
/*   Updated: 2025/10/17 16:48:45 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*exec_external2(char **argv, t_cmd *cmd, t_shell *stru)
{
	struct stat	info;
	char		*path_val;
	char		*chosen_path;

	if (argv == NULL || argv[0] == NULL)
		return (NULL);
	if (ft_strchr(argv[0], '/'))
	{
		if (stat(argv[0], &info) != 0 && cmd->fd_out_put1 == -2
			&& cmd->fd_out_put2 == -2)
			return (err_msg_file_or_dir(argv, stru), NULL);
		else if (S_ISDIR(info.st_mode))
			return (err_msg_dir(argv, stru), NULL);
		return (argv[0]);
	}
	path_val = get_env_value(stru->environ, "PATH");
	if ((path_val == NULL || path_val[0] == '\0')
		&& cmd->fd_out_put1 == -2 && cmd->fd_out_put2 == -2)
		return (err_msg_file_or_dir(argv, stru), NULL);
	chosen_path = find_in_path(argv[0], stru);
	if (!chosen_path)
		return (err_msg_cmd(argv, stru), NULL);
	return (chosen_path);
}

void	handle_exec_error(t_ext *ext, t_shell *stru, int error)
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
	close_fd(cmd);
	if (execve(ext.chosen_path, ext.argv, ext.envp) == -1)
		handle_exec_error(&ext, stru, errno);
}

int	collect_status(pid_t pid, t_shell *stru)
{
	int	status;

	(void)stru;
	status = 0;
	waitpid(pid, &status, 0);
	return (status);
}
