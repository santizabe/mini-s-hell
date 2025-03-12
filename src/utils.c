/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:20:25 by szapata-          #+#    #+#             */
/*   Updated: 2025/03/07 12:22:03 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		printf("[%d]: %s\n", i, array[i]);
		i++;
	}
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	*my_getenv(char *str, char **env)
{
	int		strlen;

	strlen = ft_strlen(str);
	while (*env)
	{
		if (!ft_strncmp(str, *env, strlen) && (*env)[strlen] == '=')
			return (&((*env)[strlen + 1]));
		env++;
	}
	return (NULL);
}

void	ft_file_clear(t_list *files_lst)
{
	t_redir	*file;

	file = NULL;
	while (files_lst)
	{
		file = (t_redir *)files_lst->content;
		free(file->file);
		file->file = NULL;
		files_lst = files_lst->next;
	}
}
