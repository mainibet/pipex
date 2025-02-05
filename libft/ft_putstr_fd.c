/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albetanc <albetanc@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:17:33 by albetanc          #+#    #+#             */
/*   Updated: 2024/12/17 17:22:50 by albetanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	if (s == NULL)
		return (-1);
	len = ft_strlen(s);
	if (safe_write(fd, s, len) == -1)
		return (-1);
	return (1);
}
