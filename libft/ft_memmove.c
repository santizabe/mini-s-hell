/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:28:04 by szapata-          #+#    #+#             */
/*   Updated: 2023/12/12 09:49:26 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*udst;
	unsigned char	*usrc;

	udst = dst;
	usrc = (unsigned char *) src;
	if (dst < src)
		return (ft_memcpy(dst, src, len));
	if (dst > src)
	{
		udst += len - 1;
		usrc += len - 1;
		while (len--)
			*udst-- = *usrc--;
	}
	return (dst);
}
