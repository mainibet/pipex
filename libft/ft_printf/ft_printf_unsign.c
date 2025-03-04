/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_unsign.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albetanc <albetanc@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:49:27 by albetanc          #+#    #+#             */
/*   Updated: 2024/12/18 11:24:25 by albetanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	count_dig(unsigned int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

int	ft_printf_unsign(unsigned int n)
{
	int	len;

	if (n == 0)
	{
		if (safe_write(1, "0", 1) == -1)
			return (-1);
	}
	else
		ft_putnbr_fd_un(n, 1);
	len = count_dig(n);
	return (len);
}
