/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_write.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albetanc <albetanc@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:08:47 by albetanc          #+#    #+#             */
/*   Updated: 2024/12/18 11:10:35 by albetanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	safe_write(int fd, const void *buf, size_t count)
{
	if (write (fd, buf, count) == -1)
		return (-1);
	return (1);
}
