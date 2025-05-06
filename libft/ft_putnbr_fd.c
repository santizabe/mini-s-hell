/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 12:52:16 by szapata-          #+#    #+#             */
/*   Updated: 2023/12/20 13:35:19 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static void	ft_putnbr_helper(int n, int fd)
{
	int	minus;
	int	res;

	if (!n)
		return ;
	minus = 1;
	if (n < 0)
		minus = -1;
	res = ((n % 10) * minus);
	ft_putnbr_helper(n / 10, fd);
	ft_putchar_fd(res + 48, fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (!n)
		ft_putchar_fd('0', fd);
	if (n < 0)
		ft_putchar_fd('-', fd);
	ft_putnbr_helper(n, fd);
}
