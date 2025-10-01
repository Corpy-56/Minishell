/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fields_splitting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:20:54 by skuor             #+#    #+#             */
/*   Updated: 2025/10/01 17:26:15 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


size_t	count_fields(const char *str, const char *ifs)
{
	size_t	i;
	size_t	n_fields;

	i = 0;
	n_fields = 0;
	if (!str || !*str)
		return (0);
	while (str[i])
	{
		while (str[i] && is_ifs(str[i], ifs))
			i++;
		if (!str[i])
			break ;
		n_fields++;
		while (str[i] && !is_ifs(str[i], ifs))
		{
			if (is_quote(str[i]))
				skip_quoted(str, &i);
			else
				i++;
		}
	}
	return (n_fields);
}

char	**split_by_ifs(const char *str, const char *ifs)
{
	size_t	i;
	size_t	j;
	size_t	n_fields;
	size_t	start;
	char	**fields;

	i = 0;
	j = 0;
	fields = NULL;
	if (str == NULL)
	{
		fields = ft_calloc(1, sizeof(char *));
		return (fields);
	}
	if (!ifs || !*ifs)
		ifs = " \t\n";
	else if (!ifs[0])
	{
		fields = ft_calloc(1, sizeof(char *));
		if (fields == NULL)
			return (NULL);
		return (fields);
	}
	n_fields = count_fields(str, ifs);
	fields = ft_calloc(n_fields + 1, sizeof(char *));
	if (!fields)
		return (NULL);
	while (str[i])
	{
		if (str[i] && is_ifs(str[i], ifs))
			i++;
		if (!str[i])
			break ;
		start = i;
		while (str[i] && !is_ifs(str[i], ifs))
		{
			if (is_quote(str[i]))
				skip_quoted(str, &i);
			else
				i++;
		}
		fields[j] = ft_substr(str, start, (i - start));
		if (!fields[j])
		{
			free_fields(fields, j);
			return (NULL);
		}
		j++;
	}
	fields[j] = NULL;
	return (fields);
}

void	no_fields(char **fields, t_tokens *curr, t_tokens *prev, t_tokens *head)
{
	t_tokens	*next;

	next = curr->next;
	free(curr->str);
	free(curr);
	if (prev == NULL)
		head = next;
	else
		prev->next = next;
	free_doublechar(fields);
	curr = next;
}

void	while_fields(char **fields, size_t i, t_tokens *last)
{
	t_tokens	*new;

	while (fields[i])
	{
		new = ft_calloc(1, sizeof(*new));
		if (!new)
		{
			free_doublechar(fields);
			return ;
		}
		new->str = ft_strdup(fields[i]);
		new->next = last->next;
		last->next = new;
		last = new;
		i++;
	}
}

void	split_all_tokens(t_tokens *head, t_shell *stru)
{
	char		*ifs;
	char		**fields;
	size_t		i;

	auto t_tokens * prev, *current, *last;
	ifs = get_env_value(stru->environ, "IFS");
	if (!ifs || !*ifs)
		ifs = " \t\n";
	prev = NULL;
	current = head;
	while (current)
	{
		if (is_operator(current->str))
		{
			prev = current;
			current = current->next;
			continue ;
		}
		fields = split_by_ifs(current->str, ifs);
		if (!fields)
			return ;
		if (fields[0] == NULL)
		{
			no_fields(fields, current, prev, head);
			continue ;
		}
		free(current->str);
		current->str = ft_strdup(fields[0]);
		if (!current->str)
			return (free_doublechar(fields));
		last = current;
		i = 1;
		while_fields(fields, i, last);
		free_doublechar(fields);
		prev = last;
		current = last->next;
	}
}
