/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albetanc <albetanc@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:11:56 by albetanc          #+#    #+#             */
/*   Updated: 2024/11/25 14:11:59 by albetanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*needle == '\0')
		return ((char *) haystack);
	while (i < len && haystack[i])
	{
		j = 0;
		while (needle[j] && (i + j) < len
			&& haystack[i + j] == needle[j])
			j++;
		if (needle[j] == '\0')
			return ((char *) &haystack[i]);
		i++;
	}
	return (NULL);
}
