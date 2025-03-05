/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 23:56:06 by szapata-          #+#    #+#             */
/*   Updated: 2025/02/26 14:39:36 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	quote_remove(char *str)
{
	char	q;
	char	d_q;

	q = 0;
	d_q = 0;
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
}

void	args_quote_remove(t_list *lst)
{
	char	*str;

	str = NULL;
	while (lst)
	{
		str = (char *)lst->content;
		quote_remove(str);
		lst = lst->next;
	}
}

void	file_quote_remove(t_list *lst)
{
	t_redir	*redir;

	redir = NULL;
	while (lst)
	{
		redir = (t_redir *)lst->content;
		if (redir->mode != -1)
			quote_remove(redir->file);
		lst = lst->next;
	}
}

int	remove_quotes(t_cmd *cmd_lst)
{
	while (cmd_lst)
	{
		args_quote_remove(cmd_lst->w_lst);
		file_quote_remove(cmd_lst->in_redir);
		file_quote_remove(cmd_lst->out_redir);
		cmd_lst = cmd_lst->next;
	}
	return (0);
}
