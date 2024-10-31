/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 00:13:54 by szapata-          #+#    #+#             */
/*   Updated: 2023/12/12 00:13:35 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int		dest_len;
	unsigned int		src_len;
	unsigned int		i;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	if (size <= dest_len)
		return (size + src_len);
	size = size - dest_len;
	i = 0;
	while (*src && i < size - 1)
	{
		dest[dest_len + i] = *src;
		src++;
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest_len + src_len);
}
