/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:10:14 by sarah             #+#    #+#             */
/*   Updated: 2025/09/08 12:18:55 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_in_path(char *name, char *path_val)
{
	char	**rep;
	char	*base;
	char	*chosen_path;
	char	*tmp;
	struct stat	info;
	int		i;

	i = 0;	
	if (!name || !path_val)
		return (NULL);
	while (name[i])
	{
		if (name[i] == '/')
			return (NULL);
		i++;
	}
	rep = ft_split(path_val, ':');
	if (rep == NULL)
		return (NULL);
	i = 0;
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
		free_split(rep);
		return (chosen_path);
	}
	free_split(rep);
	return (NULL);
}

void    run_external(t_cmd *cmd, t_shell *stru, char **env)
{
    int     pid;
	int		i;
	char	*path_val;
	char	*chosen_path;
    char    **argv;

	argv = cmd->args;
	if (argv == NULL || argv[0] == NULL)
		return ;
    pid = fork();
	if (pid < 0)
	{
		stru->last_status = 1;
		return ;
	}
	i = 0;
    if (pid == 0)
    {
       	while (argv[i])
		{
			if (argv[i] == '/')
            	execve(argv[0], argv, env);
			i++;
		}
		path_val = get_env_value(stru->environ, "PATH");
		if (path_val == NULL || path_val == "")
		{
			printf("bash: %s: command not found\n", argv[0]);
			exit(127);
		}	
		chosen_path = find_in_path(argv[0], path_val);
		if (chosen_path)
			execve(chosen_path, argv, env);
		else
		{
			printf("bash: %s: command not found\n", argv[0]);
			exit(127);
		}
    }
}