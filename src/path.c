/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:22:59 by szapata-          #+#    #+#             */
/*   Updated: 2025/02/26 13:23:19 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_path_line(char **env)
{
	char	*path_line;
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			path_line = env[i];
		i++;
	}
	path_line = path_line + 5;
	return (path_line);
}

char	*get_path(char *command, char **env)
{
	char	*path_line;
	char	**path_array;
	char	*path_final;
	int		i;
	char	*temp;

	i = 0;
	if (command[0] == '/')
		return (command);
	path_line = get_path_line(env);
	path_array = ft_split(path_line, ':');
	while (path_array[i])
	{
		temp = ft_strjoin(path_array[i], "/");
		path_final = ft_strjoin(temp, command);
		free(temp);
		if (access(path_final, F_OK) == 0)
			return (path_final);
		free(path_final);
		i++;
	}
	free_array(path_array);
	return (NULL);
}
