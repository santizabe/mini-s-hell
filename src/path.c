/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:22:59 by szapata-          #+#    #+#             */
/*   Updated: 2025/03/10 19:31:18 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_cmd_err(char *cmd)
{
	ft_putstr_fd("Command '", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd("' not found\n", STDERR_FILENO);
}

char	*get_path_line(char **env)
{
	char	*path_line;
	int		i;

	i = 0;
	path_line = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			path_line = env[i];
		i++;
	}
	if (path_line)
		path_line = path_line + 5;
	return (path_line);
}

char	*get_path(char *command, char **env)
{
	char	*path_line;
	char	**path_array;
	char	*path_final;
	int		i;

	i = 0;
	if (command[0] == '/')
		return (ft_strdup(command));
	path_line = get_path_line(env);
	if (!path_line)
		return (ft_strdup(command));
	path_array = ft_split(path_line, ':');
	while (path_array[i])
	{
		path_line = ft_strjoin(path_array[i], "/");
		path_final = ft_strjoin(path_line, command);
		free(path_line);
		if (access(path_final, F_OK) == 0)
			return (path_final);
		free(path_final);
		i++;
	}
	free_array(path_array);
	print_cmd_err(command);
	return (NULL);
}
