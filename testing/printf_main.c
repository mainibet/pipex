/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albetanc <albetanc@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:21:25 by albetanc          #+#    #+#             */
/*   Updated: 2024/12/15 14:47:01 by albetanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf/ft_printf.h"
#include "libft.h"
#include <stdio.h>
#include <limits.h>

int	main(void)
{
	char	c = 'A';
	char	str[] = "Hello world!";
	int	n = 42;
	int	nb = 42; 
	char	*ptr = &c;

	//%c
	ft_printf("My char: %c\n", c);
	printf("System's: %c\n", c);
	printf("\n");

	//%s
	ft_printf("My str: %s\n", str);
	printf("System's: %s\n", str);
	printf("\n");

	//%p
	ft_printf("My ptr: %p\n", ptr);
	printf("System's: %p\n", ptr);
	printf("\n");

	//%d
	ft_printf("My decimal number: %d\n", n);
	printf("System's: %d\n", n);
	printf("\n");

	//%i
	ft_printf("My integer base 10: %i\n", n);
	printf("System's: %i\n", n);
	printf("\n");

	//%u
	ft_printf("My unsigned decimal number: %u\n", nb);
	printf ("System's: %u\n", n);
	printf("\n");

	//%x
	ft_printf("My hexadecimal lowercase: %x\n", nb);
	printf("System's: %x\n", n);
	printf("\n");
	
	//%X
	ft_printf("My hexadecimal UPPERCASE: %X\n", nb);
	printf("System's: %X\n", n);
	printf("\n");

	//%%
	ft_printf("My percetage: %%\n");
	printf("System's: %%\n");
	printf("\n");

	//additional testing ptr
	printf("\npointer test: \n");
	printf(" %p \n", (void *)-1);
	printf(" %p \n", (void *)1);
	printf(" %p \n", (void *)15);
	printf(" %p \n", (void *)16);
	printf(" %p \n", (void *)17);
	printf(" %p %p \n", (void *)LONG_MIN, (void *)LONG_MAX);
	printf(" %p %p \n", (void *)INT_MIN, (void *)INT_MAX);
	printf(" %p %p \n", (void *)ULONG_MAX, (void *)-ULONG_MAX);
	printf("%p\n", (void *)0);
	printf("\nour pointer test: \n");
	ft_printf(" %p \n", (void *)-1);
	ft_printf(" %p \n", (void *)1);
	ft_printf(" %p \n", (void *)15);
	ft_printf(" %p \n", (void *)16);
	ft_printf(" %p \n", (void *)17);
	ft_printf(" %p %p \n", (void *)LONG_MIN, (void *)LONG_MAX);
	ft_printf(" %p %p \n", (void *)INT_MIN, (void *)INT_MAX);
	ft_printf(" %p %p \n", (void *)ULONG_MAX, (void *)-ULONG_MAX);
	ft_printf("%p\n", (void *)0);

	//additional testing hexa
	printf("\n unsigned test: \n");
	printf("%u\n", 0);
	printf("%u\n", -1);
	printf("%u\n", 1);
	printf("%u\n", 9);
	printf("%u\n", 10);
	printf("%u\n", 11);
	printf("%u\n", 15);
	printf("%u\n", 16);
	printf("%u\n", 17);
	printf("%u\n", 99);
	printf("%u\n", 100);
	printf("%u\n", 101);
	printf("%u\n", -9);
	printf("%u\n", -10);
	printf("%u\n", -11);
	printf("%u", -14);
	printf("%u\n", -15);
	printf("%u\n", -16);
	printf("%u\n", -99);
	printf("%u\n", -100);
	printf("%u\n", -101);
	printf("%u\n", INT_MAX);
	printf("%u\n", INT_MIN);
/*	printf("Not be the same: %u\n", LONG_MAX);
	printf("Not be the same: %u\n", LONG_MIN);
	printf("%u\n", UINT_MAX);
	printf("Not be the same: %u\n", ULONG_MAX);
	printf("Not be the same: %u\n", 9223372036854775807LL);
	printf("%u\n %u\n %lu\n %lu\n %lu\n %u\n %u\n", INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);

	printf("\nMy testing u:\n");
	ft_printf("%u\n", 0);
	ft_printf("%u\n", -1);
	ft_printf("%u\n", 1);
	ft_printf("%u\n", 9);
	ft_printf("%u\n", 10);
	ft_printf("%u\n", 11);
	ft_printf("%u\n", 15);
	ft_printf("%u\n", 16);
	ft_printf("%u\n", 17);
	ft_printf("%u\n", 99);
	ft_printf("%u\n", 100);
	ft_printf("%u\n", 101);
	ft_printf("%u\n", -9);
	ft_printf("%u\n", -10);
	ft_printf("%u\n", -11);
	ft_printf("%u", -14);
	ft_printf("%u\n", -15);
	ft_printf("%u\n", -16);
	ft_printf("%u\n", -99);
	ft_printf("%u\n", -100);
	ft_printf("%u\n", -101);
	ft_printf("INT MAX: %u\n", INT_MAX);
	ft_printf("INT MIN: %u\n", INT_MIN);
	ft_printf("LONG MAX: %u\n", LONG_MAX);
	ft_printf("LONG MIN: %u\n", LONG_MIN);
	ft_printf("UINT_MAX: %u\n", UINT_MAX);
	ft_printf("ULONG_MAX: %u\n", ULONG_MAX);
	ft_printf("LL: %u\n", 9223372036854775807LL);
	ft_printf("MIX of INTs: %u\n %u\n %u\n %u\n %u\n %u\n %u\n", INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
*/
	return (0);
}
