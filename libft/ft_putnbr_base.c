/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albetanc <albetanc@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:56:39 by albetanc          #+#    #+#             */
/*   Updated: 2024/12/11 13:19:11 by albetanc         ###   ########.fr       */
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

void	ft_putnbr_base(long long n, char *base)
{
	int				val;
	unsigned long	len;
	unsigned long	nb;

	val = valid_base(base);
	if (!val)
		return ;
	len = ft_strlen(base);
	if (n < 0)
	{
		ft_putchar_fd('-', 1);
		nb = (unsigned long)(-n);
	}
	else
		nb = (unsigned long)n;
	if (nb >= len)
		ft_putnbr_base(nb / len, base);
	ft_putchar_fd(base[nb % len], 1);
}
