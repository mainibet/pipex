/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albetanc <albetanc@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:14:40 by albetanc          #+#    #+#             */
/*   Updated: 2024/12/02 16:58:17 by albetanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_nbword(const char *s, char c)
{
	size_t	count;
	size_t	inword;

	inword = 0;
	count = 0;
	while (*s)
	{
		if (*s != c && !inword)
		{
			inword = 1;
			count++;
		}
		else if (*s == c)
			inword = 0;
		s++;
	}
	return (count);
}

static const char	*skipd(const char *s, char c)
{
	while (*s && *s == c)
		s++;
	return (s);
}

static char	*ft_subs(const char **arr, char c)
{
	size_t		wlen;
	const char	*orig;
	char		*word;

	orig = *arr;
	wlen = 0;
	while ((*arr)[wlen] && (*arr)[wlen] != c)
		wlen++;
	word = malloc((wlen + 1) * sizeof (char ));
	if (!word)
		return (NULL);
	ft_strlcpy(word, orig, wlen + 1);
	*arr += wlen;
	return (word);
}

static void	free_arr(char **arr, size_t i)
{
	while (i > 0)
		free (arr[--i]);
	free (arr);
}

char	**ft_split(const char *s, char c)
{
	char	**arr;
	size_t	nbword;
	size_t	i;

	if (!s)
		return (NULL);
	nbword = ft_nbword(s, c);
	arr = malloc((nbword + 1) * sizeof (char *));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < nbword)
	{
		s = skipd(s, c);
		arr[i] = ft_subs(&s, c);
		if (!arr[i])
		{
			free_arr(arr, i);
			return (NULL);
		}
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
