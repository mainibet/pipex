/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albetanc <albetanc@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:19:28 by albetanc          #+#    #+#             */
/*   Updated: 2024/11/25 13:35:57 by albetanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t				i;
	unsigned char		a;
	const unsigned char	*ptr;

	a = (unsigned char) c;
	ptr = (const unsigned char *) str;
	i = 0;
	while (i < n)
	{
		if (ptr[i] == a)
			return ((void *)(&ptr[i]));
		i++;
	}
	return (NULL);
}
