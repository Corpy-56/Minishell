/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hide_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouin <agouin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:39:18 by agouin            #+#    #+#             */
/*   Updated: 2025/10/14 16:36:09 by agouin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static struct termios	g_orig_termios;
struct termios			g_saved_term;

char	*join_three_char(char *a, char *b, char *c)
{
	char	*ab;
	char	*abc;

	ab = ft_strjoin(a, b);
	if (ab)
		abc = ft_strjoin(ab, c);
	else
		abc = NULL;
	free(ab);
	return (abc);
}

t_shell	*static_struct(t_shell *stru)
{
	static t_shell	*tmp = NULL;

	if (stru)
		tmp = stru;
	return (tmp);
}

void	disable_echoctl(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return ;
	g_orig_termios = term;
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	save_termios(void)
{
	tcgetattr(STDIN_FILENO, &g_saved_term);
}

void	restore_termios(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &g_saved_term);
}
