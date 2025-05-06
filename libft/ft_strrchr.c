/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 10:03:12 by szapata-          #+#    #+#             */
/*   Updated: 2023/12/12 11:46:51 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned int	len;

	len = ft_strlen(s);
	if (*(s + len) == (unsigned char) c)
		return ((char *)s + len);
	while (len--)
		if (*(s + len) == (unsigned char) c)
			return ((char *)s + len);
	return (0);
}
