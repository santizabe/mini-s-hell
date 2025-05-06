/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:52:36 by szapata-          #+#    #+#             */
/*   Updated: 2023/12/12 00:01:20 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned int	i;
	unsigned char	_c;
	unsigned char	*tmp;

	tmp = (unsigned char *) b;
	i = 0;
	_c = c;
	while (i < len)
	{
		*tmp = _c;
		i++;
		tmp++;
	}
	return (b);
}
