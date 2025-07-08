/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:31:56 by skuor             #+#    #+#             */
/*   Updated: 2025/02/12 14:55:12 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

int		ft_printf(const char *format, ...);
int		ft_putchar(char c);
int		ft_nbrlen(long nbr);
int		ft_putstr(char *str);
int		ft_putnbr_u(unsigned int nb);
int		ft_hexa(unsigned int n, char s);
int		ft_hexaptr(unsigned long int n);

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_puthex(unsigned int nb, char s);
void	ft_puthexptr(unsigned long int n);
void	ft_putnbr(int nb);

#endif