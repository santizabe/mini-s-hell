/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 20:21:34 by szapata-          #+#    #+#             */
/*   Updated: 2025/03/24 18:09:20 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_2(t_cmd *cmds, t_data *data, char *path, char **av)
{
	cmds = cmds->next;
	if (!ft_isbuiltin(av[0]))
	{
		execve(path, av, data->env);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		main_builtin(cmds, data);
		exit(EXIT_SUCCESS);
	}
}
