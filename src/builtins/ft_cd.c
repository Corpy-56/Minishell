/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 21:35:08 by skuor             #+#    #+#             */
/*   Updated: 2025/07/14 22:40:53 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char *rl, char **args)
{
	//int	i;
	char *pwd;
	(void)args;

	//i = 1;
	if (ft_strncmp(rl, "cd", 3) == 0)
	{
		pwd = getcwd(NULL, 0);
		printf("%s\n", pwd);
		if (args[1])
		{
			chdir("/home/sarah/Documents");
			pwd = getcwd(NULL, 0);
			printf("%s\n", pwd);
		}
	}
	return (0);
}