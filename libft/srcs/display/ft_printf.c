/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuor <skuor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 10:03:46 by skuor             #+#    #+#             */
/*   Updated: 2025/02/12 09:52:25 by skuor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_format(va_list list_arg, const char format)
{
	int	count;

	count = 0;
	if (format == 'c')
		count = count + ft_putchar(va_arg(list_arg, int));
	else if (format == 's')
		count = count + ft_putstr(va_arg(list_arg, char *));
	else if (format == 'd' || format == 'i')
		count = count + ft_nbrlen(va_arg(list_arg, int));
	else if (format == '%')
		count = count + ft_putchar('%');
	else if (format == 'u')
		count = count + ft_putnbr_u(va_arg(list_arg, unsigned int));
	else if (format == 'x' || format == 'X')
		count += ft_hexa(va_arg(list_arg, unsigned int), format);
	else if (format == 'p')
		count = count + ft_hexaptr(va_arg(list_arg, unsigned long int));
	else
		return (-1);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list		list_arg;
	int			i;
	int			count;

	i = 0;
	count = 0;
	va_start(list_arg, format);
	if (!format)
		return (-1);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			count = count + ft_format(list_arg, format[i]);
		}
		else
			count = count + ft_putchar(format[i]);
		i++;
	}
	va_end(list_arg);
	return (count);
}

/* int	main()
{
	static char	*i = NULL;
	//unsigned int	u;

	//u = 88;

	printf("%d\n", ft_printf("%p\n", i));
	printf("%d\n", printf("%p\n", i));

	return (0);
} */