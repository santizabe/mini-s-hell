/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 23:56:06 by szapata-          #+#    #+#             */
/*   Updated: 2025/02/26 13:04:11 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char    *remove_quotes(char *str)
{
	char    *tmp;
	char    q;
	char    d_q;

	q = 0;
	d_q = 0;
	tmp = str;
	while (str && *str)
	{
		if (*str == '\"' && !(q % 2) && ++d_q)
		{
			ft_memmove(str, str + 1, ft_strlen(str + 1) + 1);
			str = ft_strchr(str, '\"');
			continue ;
		}
		if (*str == '\'' && !(d_q % 2) && ++q)
		{
			ft_memmove(str, str + 1, ft_strlen(str + 1) + 1);
			str = ft_strchr(str, '\'');
			continue ;
		}
		str++;
	}
	return (tmp);
}