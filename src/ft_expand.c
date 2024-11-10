/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 22:03:04 by szapata-          #+#    #+#             */
/*   Updated: 2024/11/02 19:46:29 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	If a $ is found, it should expand the variable if 
 */

int	ft_expand(char *prompt, char flags)
{
	int	count;
	char	*res;
	char	*res2;

	count = 0;
	if (flags & 2 || flags & 16)
		return (0);
	prompt++;
	while (ft_isalpha(prompt[count]))
		count++;
	while (ft_isalnum(prompt[count]))
		count++;
	if (!count && !(flags & 1))	// if not between quotes
		return (-1);
	res = ft_substr(prompt, 0, count);
	if (!res)
		return (-1);
	res2 = getenv(res);
	return (count);
}