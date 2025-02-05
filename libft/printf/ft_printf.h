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
# include "./libft/libft.h"

int	ft_printf(const char *format, ...);
int	printf_char(char c);
int	printf_str(char *s);
int	printf_int(int n);
int	printf_hexa(unsigned int n, char input);
int	printf_ptr(unsigned long long p);
int	printf_unsign(unsigned int n);

#endif
