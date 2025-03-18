/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:55:31 by szapata-          #+#    #+#             */
/*   Updated: 2025/03/18 12:48:17 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	init_data(t_data *data, t_cmd **cmd_lst)
{
	data->prompt = NULL;
	(*cmd_lst) = (t_cmd *)malloc(sizeof(t_cmd));
	if (!(*cmd_lst))
		return (-1);
	ft_memset(*cmd_lst, 0, sizeof(t_cmd));
	return (0);
}

void	ft_clear_lst_order(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp)
	{
		tmp->content = NULL;
		tmp = tmp->next;
	}
	ft_lstclear(lst, del);
}

int	double_free(char **ptr)
{
	char	**tmp;

	tmp = ptr;
	while (ptr && *ptr)
		free(*ptr++);
	free(tmp);
	return (1);
}

int	free_data(t_data *data, t_cmd *cmd_lst, char mode)
{
	t_cmd	*tmp;

	tmp = cmd_lst;
	while (cmd_lst)
	{
		ft_lstclear(&(cmd_lst->w_lst), free);
		ft_file_clear(cmd_lst->in_redir);
		ft_file_clear(cmd_lst->out_redir);
		ft_lstclear(&(cmd_lst->in_redir), free);
		ft_lstclear(&(cmd_lst->out_redir), free);
		ft_clear_lst_order(&(cmd_lst->lst_order), free);
		tmp = cmd_lst;
		cmd_lst = cmd_lst->next;
		free(tmp);
	}
	free(data->prompt);
	if (mode == 1)
	{
		double_free(data->env);
		clear_history();
	}
	return (1);
}
