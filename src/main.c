/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:04:44 by szapata-          #+#    #+#             */
/*   Updated: 2025/03/24 12:19:54 by szapata-         ###   ########.fr       */
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
/*
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
*/

void	main_loop(t_data data, t_cmd *cmd_lst)
{
	while (1)
	{
		if (init_data(&data, &cmd_lst) == -1)
			break ;
		data.prompt = readline("MiniShell> ");
		if (data.prompt)
		{
			if (*(data.prompt))
			{
				add_history(data.prompt);
				if (!ft_parse(data, cmd_lst))
					if (!ft_expand(cmd_lst, data.env)
						&& !remove_quotes(cmd_lst))
						ft_execute(cmd_lst, &data);
			}
		}
		else
			break ;
		free_data(&data, cmd_lst, 0);
	}
	free_data(&data, cmd_lst, 1);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	t_cmd	*cmd_lst;

	cmd_lst = NULL;
	signals();
	if (argc++ && argv++ && copy_env(&(data.env), env) == -1)
		return (-1);
	main_loop(data, cmd_lst);
	return (0);
}
