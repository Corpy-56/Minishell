/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_tokenisation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 16:30:30 by skuor             #+#    #+#             */
/*   Updated: 2025/10/17 19:46:35 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_test_minishell(t_tokens *a_debut)
{
	int			i;
	t_tokens	*p_actuel;

	i = 0;
	p_actuel = a_debut;
	while (p_actuel != NULL)
	{
		if (p_actuel->str != NULL)
		{
			if (ft_strncmp(p_actuel->str, "./minishell",
					ft_strlen(p_actuel->str)) == 0)
			{
				ft_ignore_signal();
				i++;
				if (i >= 2)
					printf("minishell: recursive execution blocked\n");
			}
		}
		p_actuel = p_actuel->next;
	}
}

int	ft_init_tokenisation(char *rl, int i)
{
	int	k;

	if (!rl || rl[0] == '\0')
		return (-1);
	i = white_space(rl, i);
	if (i < 0)
		return (-1);
	k = ft_quote(rl, 0);
	if (k == -1)
		return (-1);
	return (0);
}
