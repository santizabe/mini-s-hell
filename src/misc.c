/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 09:59:24 by szapata-          #+#    #+#             */
/*   Updated: 2025/03/07 10:01:22 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_ismeta(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int	ft_isdelimiter(char c)
{
	if (c == '>' || c == '<' || c == '|' || c == ' ' || c == '\0')
		return (1);
	return (0);
}

int	ft_free(void *ptr)
{
	free(ptr);
	return (1);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (s2);
	else if (!s2)
		return (s1);
	return (ft_strjoin(s1, s2));
}
