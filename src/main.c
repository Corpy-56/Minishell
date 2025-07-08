/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:39:18 by agouin            #+#    #+#             */
/*   Updated: 2025/07/06 12:39:20 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"

//il faut compiler avec cc main.c -lreadline

int main(void)
{
    char *rl;
	char *pwd;

	while(1)
	{
		rl = readline("Minishell > ");
		ft_tokenisation();
		if(ft_strncmp(rl, "pwd", 4) == 0)
		{
			pwd = getcwd(NULL, 0);
			printf("%s\n", pwd);
		}
		if (ft_strncmp(rl, "env", 4) == 0)
		{
			int i;

			i = 0;
			while(__environ[i])
			{
				printf("%s\n", __environ[i]);
				i++;
			}
		}
	}
    return (0);
}
//les commandes peuvent rater il faut quelle retourne une valeur 