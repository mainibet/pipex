/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_ptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albetanc <albetanc@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:48:05 by albetanc          #+#    #+#             */
/*   Updated: 2024/12/18 11:23:47 by albetanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	count_dig(unsigned long long n)
{
	int				len;

	len = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		len++;
		n /= 16;
	}
	return (len);
}

int	ft_printf_ptr(unsigned long long add)
{
	char	*pref;
	char	*base;
	int		len;

	pref = "0x";
	base = "0123456789abcdef";
	if (!add)
	{
		if (safe_write(1, "(nil)", 5) == -1)
			return (-1);
		return (5);
	}
	if (safe_write(1, pref, ft_strlen(pref)) == -1)
		return (-1);
	ft_putnbr_base_un(add, base);
	len = count_dig(add);
	return (len + 2);
}
