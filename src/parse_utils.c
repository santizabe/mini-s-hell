/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:01:49 by szapata-          #+#    #+#             */
/*   Updated: 2025/03/18 12:22:39 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	set_redir_mode(t_redir *redir, int flags)
{
	if (flags & 4 || flags & 1)
	{
		redir->mode = O_RDONLY;
		if (flags & 1)
			redir->mode = -1;
	}
	else
	{
		redir->mode = O_RDWR | O_CREAT | O_TRUNC;
		if (flags & 2)
			redir->mode = O_WRONLY | O_CREAT | O_APPEND;
	}
	return (1);
}

char	set_flags(char **c)
{
	char	s;

	s = **c;
	(*c)++;
	if (s == '<' && **c == '<' && (*c)++)
		return (1);
	else if (s == '>' && **c == '>' && (*c)++)
		return (2);
	else if (s == '<')
		return (4);
	else
		return (8);
}

char	*iter_prompt(char **prompt)
{
	char	q;

	q = 0;
	while (!ft_isdelimiter(**prompt))
	{
		if (**prompt == '\'' || **prompt == '\"')
		{
			q = **prompt;
			(*prompt)++;
			(*prompt) = ft_strchr((*prompt), q);
			if (!(*prompt))
				return (NULL);
		}
		(*prompt)++;
	}
	return (*prompt);
}
