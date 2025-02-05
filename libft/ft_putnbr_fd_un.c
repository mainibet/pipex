/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd_un.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albetanc <albetanc@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:03:10 by albetanc          #+#    #+#             */
/*   Updated: 2024/12/17 16:46:32 by albetanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd_un(unsigned long n, int fd)
{
	char	buff[20];
	int		i;

	i = 0;
	if (fd < 0)
		return (-1);
	ft_bzero(buff, 20);
	if (n == 0)
	{
		if (ft_putchar_fd('0', fd) == -1)
			return (-1);
		return (1);
	}
	while (n > 0)
	{
		buff[i++] = (n % 10) + '0';
		n /= 10;
	}
	while (i--)
	{
		if (ft_putchar_fd(buff[i], fd) == -1)
			return (-1);
	}
	return (i + 1);
}
