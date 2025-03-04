/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_hexa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albetanc <albetanc@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:49:49 by albetanc          #+#    #+#             */
/*   Updated: 2024/12/17 13:28:24 by albetanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*select_base(char input)
{
	if (input == 'x')
		return ("0123456789abcdef");
	else if (input == 'X')
		return ("0123456789ABCDEF");
	else
		return (NULL);
}

static int	count_dig(unsigned int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		len++;
		n /= 16;
	}
	return (len);
}

int	ft_printf_hexa(unsigned int n, char input)
{
	char	*base;
	int		len;

	base = select_base(input);
	if (!base)
		return (-1);
	len = count_dig(n);
	ft_putnbr_base_un(n, base);
	return (len);
}
