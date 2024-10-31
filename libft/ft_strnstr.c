/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 22:22:00 by szapata-          #+#    #+#             */
/*   Updated: 2023/12/19 21:19:03 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;

	needle_len = ft_strlen(needle);
	if (*needle == '\0')
		return ((char *)haystack);
	if (!len)
		return (0);
	len = len - needle_len + 1;
	while (*haystack && len--)
	{
		if (*haystack == *needle)
			if (!ft_strncmp((char *)haystack, (char *)needle, needle_len))
				return ((char *)haystack);
		haystack++;
	}
	return (0);
}
