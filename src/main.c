/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:04:44 by szapata-          #+#    #+#             */
/*   Updated: 2025/05/06 19:38:15 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_exit_status;

int	d_ptrlen(char **ptr)
{
	int	count;

	count = 0;
	while (ptr && *ptr && ++count)
		ptr++;
	return (count);
}

/**
 * @brief Creates a duplicate of the given environment array.
 * 
 * @param dst Pointer to the destination array where the copy will be stored.
 * @param src Source environment array to copy (NULL-terminated strings).
 * @return 0 on success, -1 on allocation failure.
 * @note If src is empty or NULL, creates an empty environment array with 
 * just a NULL terminator.
 * @warning Caller is responsible for freeing the allocated memory.
 */
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

int	check_spaces(char *s)
{
	while (s && *s)
	{
		if (*s != ' ' && *s != '\t')
			return (1);
		s++;
	}
	return (0);
}

void	main_loop(t_data data, t_cmd *cmd_lst)
{
	while (1)
	{
		g_exit_status = 0;
		if (init_data(&data, &cmd_lst) == -1)
			break ;
		data.prompt = readline("\033[38;5;208mMiniShell> \033[0m");
		if (data.prompt)
		{
			if (*(data.prompt) && check_spaces(data.prompt))
			{
				add_history(data.prompt);
				if (!ft_parse(data, cmd_lst))
					if (!ft_expand(cmd_lst, &data)
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
	ft_memset(&data, 0, sizeof(t_data));
	signals();
	(void)argc;
	(void)argv;
	if (copy_env(&(data.env), env) == -1)
		return (-1);
	init_msg();
	main_loop(data, cmd_lst);
	return (0);
}
