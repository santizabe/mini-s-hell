/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:04:44 by szapata-          #+#    #+#             */
/*   Updated: 2025/03/17 14:54:14 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	d_ptrlen(char **ptr)
{
	int	count;

	count = 0;
	while (ptr && *ptr && ++count)
		ptr++;
	return (count);
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

int	copy_env(char ***dst, char **src)
{
	int	env_len;
	int	i;

	env_len = d_ptrlen(src);
	if (!env_len)
		env_len = 1;
	(*dst) = (char **)malloc((env_len + 1) * sizeof(char *));
	if (!(*dst))
		return (-1);
	(*dst)[env_len] = NULL;
	i = 0;
	while (src && *src && i < env_len)
	{
		(*dst)[i] = ft_strdup(src[i]);
		if (!(*dst)[i] && double_free((*dst)))
			return (-1);
		i++;
	}
	return (0);
}

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

int	free_data(t_data *data, t_cmd *cmd_lst, char mode)
{
	ft_lstclear(&(cmd_lst->w_lst), free);
	ft_file_clear(cmd_lst->in_redir);
	ft_file_clear(cmd_lst->out_redir);
	ft_lstclear(&(cmd_lst->in_redir), free);
	ft_lstclear(&(cmd_lst->out_redir), free);
	ft_clear_lst_order(&(cmd_lst->lst_order), free);
	free(cmd_lst);
	free(data->prompt);
	if (mode == 1)
	{
		double_free(data->env);
		clear_history();
	}
	return (1);
}

int	print_data(t_cmd *cmd_lst)
{
	t_redir	*redir;
	t_list	*tmp;

	while (cmd_lst)
	{
		tmp = cmd_lst->w_lst;
		while (tmp)
		{
			printf("%s, ", (char *)tmp->content);
			tmp = tmp->next;
		}
		printf("\n");
		tmp = cmd_lst->in_redir;
		while (tmp)
		{
			redir = (t_redir *)tmp->content;
			printf("%s, ", redir->file);
			tmp = tmp->next;
		}
		printf("\n");
		tmp = cmd_lst->out_redir;
		while (tmp)
		{
			redir = (t_redir *)tmp->content;
			printf("%s, ", redir->file);
			tmp = tmp->next;
		}
		printf("\n ----------------------\n");
		cmd_lst = cmd_lst->next;
	}
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	t_cmd	*cmd_lst;
	signals();
	if (argc++ && argv++ && copy_env(&(data.env), env) == -1)
		return (-1);
	while (1)
	{
		if (init_data(&data, &cmd_lst) == -1)
			break ;
		data.prompt = readline("MiniShell> ");
		if (data.prompt)
		{
			if (*(data.prompt))
			{
				if (!ft_strncmp("exit", data.prompt, 4))
					break ;
				add_history(data.prompt);
				if (!ft_parse(data, cmd_lst))
					if (!ft_expand(cmd_lst, data.env) && !remove_quotes(cmd_lst))
						ft_execute(cmd_lst, &data);
			}
		}
		else 
			break ;
		free_data(&data, cmd_lst, 0);
	}
	free_data(&data, cmd_lst, 1);
	return (0);
}
