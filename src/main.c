/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:39:18 by agouin            #+#    #+#             */
/*   Updated: 2025/07/15 11:34:13 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//il faut compiler avec cc main.c -lreadline

int	main(void)
{
	char	*rl;
	char	**args;

	args = NULL;
	while (1)
	{
		rl = readline("Minishell > ");
//		ft_tokenisation();
		ft_pwd(rl);
		ft_env(rl);
		ft_exit(rl, args);
		ft_echo(rl, args);
		ft_cd(rl, args);
	}
	return (0);
}

/* int	main(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("before chdir: %s\n", pwd);
	chdir("..");
	pwd = getcwd(NULL, 0);
	printf("after chdrir: %s\n", pwd);
	return (0);
} */
