/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albetanc <albetanc@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:47:51 by albetanc          #+#    #+#             */
/*   Updated: 2024/12/17 11:00:22 by albetanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	safe_putstr(char *s)
{
	if (write(1, s, ft_strlen(s)) == -1)
		return (-1);
	return (1);
}

int	ft_printf_str(char *s)
{
	size_t			len;

	if (!s)
	{
		if (safe_putstr("(null)") == -1)
			return (-1);
		return (6);
	}
	len = ft_strlen(s);
	if (safe_putstr(s) == -1)
		return (-1);
	return (len);
}
