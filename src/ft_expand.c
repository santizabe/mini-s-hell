/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 22:03:04 by szapata-          #+#    #+#             */
/*   Updated: 2024/10/31 22:44:53 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	If a $ is found, it should expand the variable if 
 */

int	ft_expand(char *prompt, char flags)
{
	int	count;

	count = 0;
	if (flags & 2 || flags & 16)
		return (0);
	prompt++;
	while (ft_isalpha(*prompt) && ++count)
		prompt++;
	while (ft_isalnum(*prompt) && ++count)
		prompt++;
	if (!count && !(flags & 2))	// if not between quotes
		return (-1);
	//strjoin prompt - count, substr(prompt - count, 0, count)
	//get env. Handle malloc errors.
}