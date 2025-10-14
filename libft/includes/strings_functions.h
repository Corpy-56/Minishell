/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_functions.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:44:14 by skuor             #+#    #+#             */
/*   Updated: 2025/10/14 17:13:18 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRINGS_FUNCTIONS_H
# define STRINGS_FUNCTIONS_H

int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);

size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t siz);
size_t	ft_strlcat(char *dst, const char *src, size_t siz);

void	ft_striteri(char *s, void (*f)(unsigned int, char*));

char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	**ft_array_dup(char **array);
char	*get_next_line(int fd);
char	*ft_strjoin_free(char const *s1, char const *s2);

#endif
