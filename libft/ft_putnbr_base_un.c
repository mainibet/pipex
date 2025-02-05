/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_un.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albetanc <albetanc@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 14:33:31 by albetanc          #+#    #+#             */
/*   Updated: 2024/12/17 16:53:39 by albetanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	valid_base(char *base)
{
	int	i;
	int	j;

	i = 0;
	if (!base || base[0] == '\0' || base[1] == '\0')
		return (0);
	if (base[i] == '+' || base[i] == '-')
		return (0);
	while (base[i])
	{
		if (!((base[i] >= '0' && base[i] <= '9')
				|| (base[i] >= 'A' && base[i] <= 'Z')
				|| (base[i] >= 'a' && base[i] <= 'z')))
			return (0);
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_putnbr_base_un(unsigned long n, char *base)
{
	int				val;
	unsigned long	len;
	unsigned long	nb;

	val = valid_base(base);
	if (!val)
		return (-1);
	len = ft_strlen(base);
	nb = (unsigned long)n;
	if (nb >= len)
		ft_putnbr_base_un(nb / len, base);
	if (safe_write(1, &base[nb % len], 1) == -1)
		return (-1);
	return (0);
}
