/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albetanc <albetanc@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:47:16 by albetanc          #+#    #+#             */
/*   Updated: 2024/12/17 10:42:28 by albetanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	safe_putchar(char c, int fd)
{
	if (write (fd, &c, 1) == -1)
		return (-1);
	return (1);
}

int	ft_printf_char(char c)
{
	if (safe_putchar(c, 1) == -1)
		return (-1);
	return (1);
}
