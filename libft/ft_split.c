/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 03:08:04 by santizabe         #+#    #+#             */
/*   Updated: 2023/12/21 14:16:12 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static	char	**free_memory(char **str_arr)
{
	char	**tmp;

	tmp = str_arr;
	while (*str_arr != NULL)
	{
		free(*str_arr);
		str_arr++;
	}
	free(tmp);
	return (NULL);
}

static	int	word_count(const char *s, char c)
{
	int	wc;

	wc = 0;
	while (s && *s)
		if (*s++ != c && ++wc)
			s = ft_strchr(s, c);
	return (wc);
}

static	int	word_len(const char *s, char c)
{
	int	wlen;

	wlen = 0;
	while (*s && *s++ != c)
		wlen++;
	return (wlen);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**str_arr;

	str_arr = (char **)malloc((word_count(s, c) + 1) * sizeof(char *));
	if (!str_arr)
		return (str_arr);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			str_arr[i] = ft_substr(s, 0, word_len(s, c));
			if (!str_arr[i])
				return (free_memory(str_arr));
			i++;
			s += word_len(s, c);
			continue ;
		}
		s++;
	}
	str_arr[i] = NULL;
	return (str_arr);
}
