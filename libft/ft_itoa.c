/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albetanc <albetanc@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:15:05 by albetanc          #+#    #+#             */
/*   Updated: 2024/12/04 16:43:43 by albetanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nb_len(long n)
{
	int	nb_len;

	nb_len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		nb_len++;
	while (n)
	{
		n /= 10;
		nb_len++;
	}
	return (nb_len);
}

static void	fill_nb(char *str, long nb, long *len)
{
	while (nb)
	{
		str[--(*len)] = (nb % 10) + '0';
		nb /= 10;
	}
}

char	*ft_itoa(int n)
{
	long	len;
	long	nb;
	char	*str;

	len = nb_len(n);
	nb = n;
	str = (char *)malloc((len + 1) * sizeof (char));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (nb == 0)
	{
		str[0] = '0';
		return (str);
	}
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	fill_nb(str, nb, &len);
	return (str);
}
