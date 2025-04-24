/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:35:26 by szapata-          #+#    #+#             */
/*   Updated: 2025/04/23 16:16:28 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_args_expand(t_list *lst, t_data *data)
{
	char	*str;

	str = NULL;
	while (lst)
	{
		str = (char *)lst->content;
		str = ft_expand_word(str, data);
		if (!str)
			return (-1);
		lst->content = str;
		lst = lst->next;
	}
	return (0);
}

int	ft_files_expand(t_list *lst, t_data *data)
{
	t_redir	*redir;

	redir = NULL;
	while (lst)
	{
		redir = (t_redir *)lst->content;
		if (redir->mode != -1)
		{
			redir->file = ft_expand_word(redir->file, data);
			if (!redir->file)
				return (-1);
		}
		lst = lst->next;
	}
	return (0);
}

int	ft_expand(t_cmd *cmd_lst, t_data *data)
{
	while (cmd_lst)
	{
		if (ft_args_expand(cmd_lst->w_lst, data) == -1)
			return (-1);
		if (ft_files_expand(cmd_lst->in_redir, data) == -1)
			return (-1);
		if (ft_files_expand(cmd_lst->out_redir, data) == -1)
			return (-1);
		cmd_lst = cmd_lst->next;
	}
	return (0);
}
