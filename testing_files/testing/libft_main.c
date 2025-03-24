/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albetanc <albetanc@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 11:25:11 by albetanc          #+#    #+#             */
/*   Updated: 2024/12/03 19:33:24 by albetanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <ctype.h> //for isalpha, isdigit, isalnum, isascii, isprint, tolower, toupper
#include "libft.h"
#include <string.h> //for strlen for memset and ft_memset. ft_memset and ft_bzero can use for size_t <stddef.h> instead of string.h, also for strrchr, strrchr, strncmp, memchr, memcpy, memmove, strnstr, strlcpy, strlcat
#include <stdlib.h> //for atoi


// Define ANSI color codes
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define NC "\033[0m" // No Color


int	main(void)
{
	//is_alpha
	
	/*
	int	c;
	c = 'a';
	printf("My isalpha 1 if is or 0 if not: %d\n", ft_isalpha(c));
	printf("System's isalpha 1024 means 1: %d\n", isalpha(c));
	*/
	
	
	
	//is_digit
	
	/*
	int	c;
	c = '9';
	printf("My issdigit 1 if it is or 0 if not: %d\n", ft_isdigit(c));
        printf("System's if 2048 is like 1: %d\n", isdigit(c));
	*/
	
	
	
	//is alnum
	
/*	
	int	c;
	c = 'A';
	printf("My alnum 1 if is and 0 if not: %d\n", ft_isalnum(c));
        printf("System's alnum: %d\n", isalnum(c));
*/	
	
	
	
	//is_ascii
	
	/*
	int	c;
	c = 128;
	printf("My isascii (non 0 if is and 0 if not): %d\n", ft_isascii(c));
	printf("System's: %d\n", isascii(c));
	*/
	
	
	
	//isprint
	
	/*
	int c;
	c = '\t'
	printf("my isprint (0 if is not a non 0 if it is): %d\n", ft_isprint(c));
        printf("system's: %d\n", isprint(c));
	*/
	
	
	
	//strlen
/*	
	char	s[] = "Hello!";
	printf("My len: %zu\n", ft_strlen(s));
	printf("System's: %lu\n", strlen(s));
*/	
	
	
	//memset
	
	/*
	char	str[] = "hello";
	int c = 'A';
        size_t n = 2;
        ft_memset(str, c, n);
        //memset(str,c, n);
        printf("My memset: %s\n", str);
        //printf("systems: %s\n", str); 
	*/


	
	//bzero
/*
	char str[] = "hello";
	size_t  n;
	size_t  i;
	
	i = 0;
	n = 2;//ft_strlen(str);To avoid stack smashin n needs to be max = strlen(str)
*/
//	bzero(str,n);
/*
	ft_bzero(str, n);
 	while (str[i] == '\0')
	{
		printf("0");
		i++;
	}
	while (str[i])//if n = size the condition needs to be i <= n. if n = o    ther # needs to be the condition while(str[i])
	{
	printf("%c", str[i]);
//	printf("%c", str[i]);
	i++;
}
*/
//memcpy
/*		
	char src[] = "Hello 42";
	char dest[20];
	
	ft_memcpy(dest, src, 4);
//	memcpy(dest, src, 4);
	dest[4] = '\0';
	printf("%s\n", dest);	
*/
/*
char buff[20] = "Hello World";
ft_memmove(buff + 6, buff, 6);
//      memmove(buff + 6, buff, 6);
printf("%s\n", buff);
*/



	//strlcpy
/*	
	char	dst[50];
	char	src[] = "Hello World!";

	ft_strlcpy(dst, src, 50);
//	strlcpy(dst, src, 50);
	printf("My strlcpy: %zu\n", ft_strlcpy(dst, src, 50));
//	printf("system's strlcpy: %lu\n", strlcpy (dst, src, 50));
	printf("intented str: %s\n", src);
*/



	//strlcat

/*
	char	dest[] = "Hello";
	const char	src[] = " World";
	size_t	dest_len = 5;

	printf("Initial dst: %s\n", dest);
	printf("Initial src: %s\n", src);
	printf("My strlcat: %zu\n", ft_strlcat(dest, src, dest_len));
	printf("System's: %lu\n", strlcat(dest, src, dest_len));
	printf("Final string: %s\n", dest);
*/


	//toupper
/*	
	char	c;

	c = 'a';
	printf("Initial: %c\n", c);
	printf("My result: %c\n", ft_toupper(c));
	printf("System's: %c\n", toupper(c));
*/

	//strchr
/*
	const char str[] = "Hello 42 Berlin!";
	int	c;

	c = '\0';
	char *my_res= ft_strchr(str,c);
	char *system_res = strchr(str,c);
	if (my_res == NULL && system_res == NULL)
		printf("the character does not appear in the string");
	else
	{
		printf("My result (first occ) of %c is in this ptr: %p\n", c, ft_strchr(str, c));
		printf("System result of %c is: %p\n", c, strchr(str, c));
	}
*/

	//strrchr
/*
	int	c;
	const char str[] = "Hello 42 Berlin";
	
	c = 'l';
	printf("Looking for the last occurance of %c\n", c);
	printf("My result: %p\n", ft_strrchr(str, c));
	printf("System's: %p\n", strrchr(str, c));
*/

	//strncmp
/*	

	const char s1[]	= "apple";
	const char s2[] = "apricot";
	size_t	n;

	n = 10;
	printf("Comparison between %s and %s the number %zu of chars\n", s1, s2, n);
	printf("My result: %d\n", ft_strncmp(s1, s2, n));
	printf("System's: %d\n", strncmp(s1, s2, n));
*/



	//memchr

/*
	const char buff[] = "Hello World!";
	int	c;
	size_t	n;
	char	*res;
	char	*syres;

	c = 'e';
	n = ft_strlen(buff);
	res = (char *)ft_memchr(buff, c, n);
	syres = (char *) memchr(buff, c, n);
	if (res != NULL && syres != NULL)
	{
		printf("Mine found '%c' at position: %ld\n", c, (long)(res - buff));
		printf("System's found '%c' at position: %ld\n", c, (long)(syres - buff));
	}
	else
		printf("Char '%c' not found.\n", c);
*/


	//memcmp

/*
	const char	buff1[] = "abcde";
	const char	buff2[] = "abzde";
	size_t		n;
	int		res;
	int		syres;

	n = 5;
	res = ft_memcmp(buff1, buff2, n);
	syres = memcmp(buff1, buff2, n);

	if (res == 0 && syres == 0)
	{
		printf("There is no difference\n");
		printf("My result: %d\n", res);
		printf("System's: %d\n", syres);
	}
	else if (res > 0 && syres > 0)
	{
		printf("Buff1 is greater than Buff2\n");
		printf("My result: %d\n", res);
		printf("System's: %d\n", syres);
	}
	else
	{
		printf("Buf2 is greater than Buff 1\n");
		printf("My result: %d\n", res);
		printf("System's: %d\n", syres);
	}
*/

	//strnstr
/*


	const char *haystack = "Hello world!";
	const char *needle = "world";
	size_t	len = 11;
	char	*res = ft_strnstr(haystack, needle, len);

	if (res)
		printf("My result: found '%s' in '%s' within the first %zu chars.\n", needle, haystack, len);
	else 
		printf("'%s' not found in '%s' withiin the first %zu chars.\n", needle, haystack, len);
*/

	//atoi
/*
	
	const char str[] = " 12abc45";
	printf("My result: %d\n", ft_atoi(str));
	printf("System's: %d\n", atoi(str));


*/


	//calloc
/*	

	int	nume = 5;
	int	*arr = (int *)ft_calloc(nume, sizeof(int));
	int	*syres = (int *)calloc(nume, sizeof(int));
	int	i;

	i = 0;
	if (arr == NULL || syres == NULL)
	{
                printf("Error assigning memory\n");
                if (arr == NULL)
                        printf("My ft_calloc failed\n");
                if (syres == NULL)
                        printf("system's failed\n");
                return (1);
        }
        printf("My result:\n");
        while (i < nume)
        {
                printf("%d ", arr[i]);
                i++;
        }
        printf("\n");
        printf("Sytem's:\n");
        i = 0;
        while (i < nume)
        {
                printf("%d ", syres[i]);
                i++;
        }
        printf("\n");
        free (arr);
        free(syres);
*/

	//strdup
/*	
        const char      *src = "Hello, World!";
        char    *my_dup = ft_strdup(src);
        char    *sy_dup = strdup(src);

        if (my_dup != NULL || sy_dup != NULL)
        {
                printf("Initial str: %s\n", src);
                printf("\033[0;32mMy reult: %s\033[0m\n", my_dup);
                printf("System's: %s\n", sy_dup);
        }
        else
                printf("\033[1;31mMemory allocation failed\033[0m\n");
*/

	//ft_split
/*	

	char    s[] = "osolperrolgatolpez";
	char    c;
	char    **arr;
	size_t  i;
	
	c = 'l';
	arr = ft_split(s, c);
	printf("Initial string: %s\n", s);
	printf("Delimiter: %c\n", c);
	i = 0;
	while (arr[i])
	{
		printf("Substring %lu: %s\n", i + 1, arr[i]);
		free(arr[i]);
		i++;
	}
	free (arr);
*/


	//ft_substr

/*

	const char str[] = "Merry christmas!";
	size_t  len = 5;
	unsigned int    start = 1;
	char    *substr = ft_substr(str, start, len);

	if (substr)
	{
		printf("\033[32mSubstring: '%s'\n\033[0m", substr    );
		printf("Initial string: %s\n", str);
		free (substr);
	}
	else
	printf("\033[31mFailed to create substring\n\033[    0m");

*/

//ft_strjoin
/*
	
	char *s1 = "Hello ";
	char *s2 = "World!";
	char *res;

	res = ft_strjoin(s1, s2);
	if (res)
		printf(GREEN "Joined str: %s\n" NC, res);
	else
		printf(RED "Error: allocation failure\n" NC);
*/

//ft_strtrim


	char const      str[] = "Hello World!";
        char const      trim[] = "World";
        char    *res;

        res = ft_strtrim(str, trim);
        if (res)
                printf (GREEN "Trimmed string: %s\n" NC, res);
        else
                printf (RED "Allocation failure\n" NC);
        free (res);


	return (0);
}
