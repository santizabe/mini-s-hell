/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 21:15:39 by santizabe         #+#    #+#             */
/*   Updated: 2023/12/21 13:45:43 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static int	digit_count(int n)
{
	int	count;

	if (!n)
		return (1);
	count = 0;
	while (n && ++count)
		n /= 10;
	return (count);
}

char	*ft_itoa(int n)
{
	int		count;
	int		minus;
	char	*str;
	char	*tmp;

	count = digit_count(n);
	minus = 1;
	if (n < 0)
		count++;
	str = (char *)malloc(count + 1);
	if (!str)
		return (str);
	tmp = str;
	str[count] = 0;
	if (n < 0 && count--)
	{
		minus = -1;
		*str++ = '-';
	}
	while (count)
	{
		str[--count] = ((n % 10) * minus) + 48;
		n /= 10;
	}
	return (tmp);
}
