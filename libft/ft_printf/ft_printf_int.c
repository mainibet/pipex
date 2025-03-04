/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albetanc <albetanc@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:42:32 by albetanc          #+#    #+#             */
/*   Updated: 2024/12/17 17:32:14 by albetanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	count_dig(int n)
{
	int	len;
	int	tmp;

	len = 0;
	tmp = n;
	if (n == 0)
		len = 1;
	if (n < 0)
		len++;
	while (tmp)
	{
		len++;
		tmp /= 10;
	}
	return (len);
}

int	ft_printf_int(int n)
{
	int	len;

	len = count_dig(n);
	if (ft_putnbr_fd_sig(n, 1) == -1)
		return (-1);
	return (len);
}
