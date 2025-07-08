/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:29:25 by skuor             #+#    #+#             */
/*   Updated: 2024/12/04 12:02:06 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	count_words(char const *str, char c)
{
	size_t	i;
	size_t	word_count;
	int		is_word;

	i = 0;
	word_count = 0;
	is_word = 0;
	while (str[i])
	{
		if (str[i] == c)
			is_word = 0;
		else if (!is_word)
		{
			is_word = 1;
			word_count++;
		}
		i++;
	}
	return (word_count);
}

static	size_t	word_len(const char *s, char c)
{
	size_t	i;
	size_t	word_len;

	i = 0;
	word_len = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			while (s[i] != c && s[i])
			{
				word_len++;
				i++;
			}
			return (word_len);
		}
		i++;
	}
	return (0);
}

static char	**ft_free(char **array, int i)
{
	int	j;

	j = 0;
	while (j <= i)
	{
		free(array[j]);
		j++;
	}
	free(array);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char		**array;
	size_t		i;
	size_t		j;
	size_t		word_count;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	array = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!array)
		return (NULL);
	array[word_count] = NULL;
	i = -1;
	j = 0;
	while (++i < word_count)
	{
		while (s[j] == c)
			j++;
		array[i] = (char *)malloc(sizeof(char) * (word_len(s + j, c) + 1));
		if (!array[i])
			return (ft_free(array, i));
		ft_strlcpy(array[i], s + j, word_len(s + j, c) + 1);
		j += word_len(s + j, c);
	}
	return (array);
}
/*
int	main(int ac, char **av)
{
	(void)ac;
	int	i;
	char 	**array;

	array = ft_split(av[1], av[2][0]);
	i = 0;
	
	while (array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
	return 0;
}
*/
