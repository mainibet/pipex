/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albetanc <albetanc@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 14:41:36 by albetanc          #+#    #+#             */
/*   Updated: 2024/12/16 14:34:50 by albetanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include "../libft.h"

int	ft_printf(const char *format, ...);
int	ft_printf_char(char c);
int	ft_printf_str(char *s);
int	ft_printf_int(int n);
int	ft_printf_hexa(unsigned int n, char input);
int	ft_printf_ptr(unsigned long long p);
int	ft_printf_unsign(unsigned int n);

#endif
