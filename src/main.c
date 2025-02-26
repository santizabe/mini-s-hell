/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:04:44 by szapata-          #+#    #+#             */
/*   Updated: 2025/02/26 13:04:45 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	history(char *input)
{
	// int	i;
	// int	strlen;

	// i = 0;
	// strlen = ft_strlen(input);
	// while (i < strlen)
	// 	if (input[i] != ' ')
	if (input != NULL && ft_strlen(input) != 0)
		add_history(input);
}

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
	(*dst) = (char **)malloc((env_len + 1) * sizeof(char *));
	if (!(*dst))
		return (-1);
	(*dst)[env_len] = NULL;
	i = 0;
	while (i < env_len)
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

int	free_data(t_data *data, t_cmd *cmd_lst)
{
	ft_lstclear(&(cmd_lst->w_lst), free);
	ft_lstclear(&(cmd_lst->in_redir), free);
	ft_lstclear(&(cmd_lst->out_redir), free);
	rl_clear_history();
	free(data->prompt);
	return (1);
}

void	print_data(t_cmd *cmd_lst)
{
	t_redir *redir;

	while (cmd_lst)
	{
	while (cmd_lst->w_lst)
	{
		printf("%s, ", (char *)cmd_lst->w_lst->content);
		cmd_lst->w_lst = cmd_lst->w_lst->next;
	}
	printf("\n");
	while (cmd_lst->in_redir)
	{
		redir = (t_redir *)cmd_lst->in_redir->content;
		printf("%s, ", redir->file);
		cmd_lst->in_redir = cmd_lst->in_redir->next;
	}
	printf("\n");
	while (cmd_lst->out_redir)
	{
		redir = (t_redir *)cmd_lst->out_redir->content;
		printf("%s, ", redir->file);
		cmd_lst->out_redir = cmd_lst->out_redir->next;
	}
	printf("\n ----------------------\n");
	cmd_lst = cmd_lst->next;
	}
}

int	main(int argc, char** argv, char **env)
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
		if (!ft_strncmp(data.prompt, "exit", 4))
			break ;
		if (data.prompt && *(data.prompt))
		{
			history(data.prompt);
			if (!ft_parse(data, cmd_lst))
				if (!ft_expand(cmd_lst, data.env) && !remove_quotes(cmd_lst))
					print_data(cmd_lst);
		}
		free_data(&data, cmd_lst);
	}
	free_data(&data, cmd_lst);
	return (0);
}
