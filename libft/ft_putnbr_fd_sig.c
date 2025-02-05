/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd_sig.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albetanc <albetanc@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:00:01 by albetanc          #+#    #+#             */
/*   Updated: 2024/12/17 17:28:58 by albetanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd_sig(long long n, int fd)
{
	char	c;

	if (n == -2147483648)
	{
		if (ft_putstr_fd("-2147483648", fd) == -1)
			return (-1);
		return (1);
	}
	if (n < 0)
	{
		if (safe_write(fd, "-", 1) == -1)
			return (-1);
		n = -n;
	}
	if (n > 9)
	{
		if (ft_putnbr_fd_sig(n / 10, fd) == -1)
			return (-1);
	}
	c = n % 10 + '0';
	return (safe_write(fd, &c, 1));
}
