/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:22:59 by szapata-          #+#    #+#             */
/*   Updated: 2025/04/23 20:26:44 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_cmd_err(char *cmd, t_data *data)
{
	ft_putstr_fd("Command '", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd("' not found\n", STDERR_FILENO);
	data->exit_status = 127;
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

char	*get_path(char *command, t_data *data)
{
	char	*path_line;
	char	**path_array;
	char	*path_final;
	int		i;

	i = 0;
	path_line = get_path_line(data->env);
	if (!path_line)
		return (ft_strdup(command));
	path_array = ft_split(path_line, ':');
	while (path_array[i])
	{
		path_line = ft_strjoin(path_array[i], "/");
		path_final = ft_strjoin(path_line, command);
		free(path_line);
		if ((access(path_final, F_OK) == 0) && free_array(path_array))
			return (path_final);
		free(path_final);
		i++;
	}
	free_array(path_array);
	print_cmd_err(command, data);
	return (NULL);
}
