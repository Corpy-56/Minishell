/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fields_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 18:07:03 by skuor             #+#    #+#             */
/*   Updated: 2025/10/08 18:07:34 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	alloc_fields(t_split *split)
{
	split->n_fields = count_fields(split->str, split->ifs);
	split->fields = ft_calloc(split->n_fields + 1, sizeof(char *));
	if (!split->fields)
		return (0);
	return (1);
}

static int	create_fields(t_split *sp)
{
	sp->fields[sp->j] = ft_substr(sp->str, sp->start, (sp->i - sp->start));
	if (!sp->fields[sp->j])
		return (0);
	sp->j++;
	return (1);
}

static char	**split_here(t_split *sp)
{
	while (sp->str[sp->i])
	{
		while (sp->str[sp->i] && is_ifs(sp->str[sp->i], sp->ifs))
			sp->i++;
		if (!sp->str[sp->i])
			break ;
		sp->start = sp->i;
		while (sp->str[sp->i] && !is_ifs(sp->str[sp->i], sp->ifs))
		{
			if (is_quote(sp->str[sp->i]))
				skip_quoted(sp->str, &sp->i);
			else
				sp->i++;
		}
		if (!create_fields(sp))
		{
			free_fields(sp->fields, sp->j);
			return (NULL);
		}
	}
	sp->fields[sp->j] = NULL;
	return (sp->fields);
}

char	**split_by_ifs(const char *str, const char *ifs)
{
	t_split	split;
	char	**split_it;

	if (str == NULL)
	{
		split.fields = ft_calloc(1, sizeof(char *));
		return (split.fields);
	}
	init_split_ifs(&split, str, ifs);
	if (!ifs[0])
	{
		split.fields = ft_calloc(1, sizeof(char *));
		if (split.fields == NULL)
			return (NULL);
		return (split.fields);
	}
	if (!alloc_fields(&split))
		return (NULL);
	split_it = split_here(&split);
	return (split_it);
}
