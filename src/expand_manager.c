/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:35:26 by szapata-          #+#    #+#             */
/*   Updated: 2025/02/26 12:44:00 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_args_expand(t_list *lst, char **env)
{
	char	*str;

	str = NULL;
	while (lst)
	{
		str = (char *)lst->content;
		str = ft_expand_word(str, env);
		if (!str)
			return (-1);
		lst->content = str;
		lst = lst->next;
	}
	return (0);
}

int	ft_files_expand(t_list *lst, char **env)
{
	t_redir	*redir;

	redir = NULL;
	while (lst)
	{
		redir = (t_redir *)lst->content;
		if (redir->mode != -1)
		{
			redir->file = ft_expand_word(redir->file, env);
			if (!redir->file)
				return (-1);
		}
		lst = lst->next;
	}
	return (0);
}

int	ft_expand(t_cmd *cmd_lst, char **env)
{
	while (cmd_lst)
	{
		if (ft_args_expand(cmd_lst->w_lst, env) == -1)
			return (-1);
		if (ft_files_expand(cmd_lst->in_redir, env) == -1)
			return (-1);
		if (ft_files_expand(cmd_lst->out_redir, env) == -1)
			return (-1);
		cmd_lst = cmd_lst->next;
	}
	return (0);
}
