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

//il faut compiler avec cc main.c -lreadline

int main(void)
{
    char *rl;
	char *pwd;

	while(1)
	{
		rl = readline("Minishell > ");
		if (rl[0] == 'p' && rl[1] == 'w' &&rl[2] == 'd')
		{
			pwd = getcwd(NULL, 0);
			printf("%s\n", pwd);
		}
    	printf("%s\n", rl);
	}
    return (0);
}
