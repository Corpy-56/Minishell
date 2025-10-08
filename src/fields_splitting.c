/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fields_splitting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:20:54 by skuor             #+#    #+#             */
/*   Updated: 2025/10/08 18:23:30 by skuor            ###   ########.fr       */
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

void	no_fields(t_split *split, t_tokens **head)
{
	t_tokens	*curr;
	t_tokens	*next;

	curr = split->current;
	next = curr->next;
	if (split->prev == NULL)
		*head = next;
	else
		split->prev->next = next;
	free(curr->str);
	free(curr);
	free_doublechar(split->fields);
	split->current = next;
}

int	while_fields(t_split *split)
{
	t_tokens	*new;

	while (split->fields[split->i])
	{
		new = ft_calloc(1, sizeof(*new));
		if (!new)
		{
			free_doublechar(split->fields);
			split->fields = NULL;
			return (-1);
		}
		new->str = ft_strdup(split->fields[split->i]);
		if (!new->str)
		{
			free(new);
			free_doublechar(split->fields);
			split->fields = NULL;
			return (-1);
		}
		new->next = split->last->next;
		split->last->next = new;
		split->last = new;
		split->i++;
	}
	return (0);
}

static void	ft_is_op(t_split *split)
{
	while (split->current)
	{
		if (is_operator(split->current->str))
		{
			split->prev = split->current;
			split->current = split->current->next;
			continue ;
		}
	}
}



void	split_all_tokens(t_tokens **head, t_shell *stru)
{
	t_split	split;

	init_split(&split, head, stru);
	ft_is_op(&split);
	while (split.current)
	{
		// if (is_operator(split.current->str))
		// {
		// 	split.prev = split.current;
		// 	split.current = split.current->next;
		// 	continue ;
		// }
		split.fields = split_by_ifs(split.current->str, split.ifs);
		if (!split.fields)
			return ;
		if (split.fields[0] == NULL)
		{
			no_fields(&split, head);
			continue ;
		}
		split.new_field = ft_strdup(split.fields[0]);
		if (!split.new_field)
			return (free_doublechar(split.fields));
		free(split.current->str);
		split.current->str = split.new_field;
		split.last = split.current;
		split.i = 1;
		if (while_fields(&split) < 0)
			return ;
		free_doublechar(split.fields);
		split.prev = split.last;
		split.current = split.last->next;
	}
}
