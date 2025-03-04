/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albetanc <albetanc@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:21:15 by albetanc          #+#    #+#             */
/*   Updated: 2024/12/18 11:59:07 by albetanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	id_type(const char *input, va_list args)
{
	int	i;

	i = 0;
	if (*input == 'c')
		i += ft_printf_char((char)va_arg(args, int));
	else if (*input == 's')
		i += ft_printf_str(va_arg(args, char *));
	else if (*input == 'p')
		i += ft_printf_ptr(va_arg(args, unsigned long long));
	else if (*input == 'd' || *input == 'i')
		i += ft_printf_int(va_arg(args, int));
	else if (*input == 'u')
		i += ft_printf_unsign(va_arg(args, unsigned int));
	else if (*input == 'x' || *input == 'X')
		i += ft_printf_hexa(va_arg(args, unsigned int), *input);
	return (i);
}

int	ft_printf(const char *input, ...)
{
	va_list			args;
	unsigned int	i;

	if (!input)
		return (-1);
	i = 0;
	va_start(args, input);
	while (*input)
	{
		if (*input == '%')
		{
			input++;
			if (ft_strchr("cspdiuxX", *input))
				i += id_type(input, args);
			else if (*input == '%')
				i += ft_printf_char('%');
			else
				return (va_end(args), -1);
		}
		else
			i = i + ft_printf_char(*input);
		input++;
	}
	va_end(args);
	return (i);
}
