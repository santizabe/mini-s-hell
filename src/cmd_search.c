/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:05:44 by szapata-          #+#    #+#             */
/*   Updated: 2025/05/06 18:13:26 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_isbuiltin(char *cmd)
{
	int	cmd_len;

	if (!cmd)
		return (0);
	cmd_len = ft_strlen(cmd);
	if (cmd_len < 2)
		cmd_len++;
	if (cmd_len && (!ft_strncmp(cmd, "cd", cmd_len)
			|| !ft_strncmp(cmd, "pwd", cmd_len)
			|| !ft_strncmp(cmd, "env", cmd_len)
			|| !ft_strncmp(cmd, "echo", cmd_len)
			|| !ft_strncmp(cmd, "export", cmd_len)
			|| !ft_strncmp(cmd, "unset", cmd_len)
			|| !ft_strncmp(cmd, "exit", cmd_len)))
		return (1);
	return (0);
}

static char	*join_path(char *dir, char *cmd, char *w_tmp)
{
	char	*tmp;
	char	*tmp2;

	tmp2 = NULL;
	tmp = ft_strjoin(dir, "/");
	if (tmp)
		tmp2 = ft_strjoin(tmp, cmd);
	free(tmp);
	free(dir);
	if (access(tmp2, F_OK))
	{
		ft_putstr_fd("Minishell: ", STDERR_FILENO);
		ft_putstr_fd(w_tmp, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		free(tmp2);
		tmp2 = NULL;
	}
	return (tmp2);
}

static char	*search_exec(char *word, char **env)
{
	char	*cwd;
	char	*fd_slash;
	char	*w_tmp;
	int		sub_lvl;

	cwd = my_getenv("PWD", env);
	cwd = ft_strdup(cwd);
	w_tmp = word;
	if (!cwd)
		return (NULL);
	sub_lvl = 0;
	while (!ft_strncmp(word, "../", 3) && ++sub_lvl)
		word = word + 3;
	if (!sub_lvl && !ft_strncmp(word, "./", 2))
		word = word + 2;
	while (sub_lvl--)
	{
		fd_slash = ft_strrchr(cwd, '/');
		*fd_slash = '\0';
	}
	return (join_path(cwd, word, w_tmp));
}

char	*search_path(char *word, t_data *data)
{
	char	*fd_slash;
	char	*path;

	path = NULL;
	fd_slash = ft_strchr(word, '/');
	if (ft_isbuiltin(word) || word[0] == '/')
		return (ft_strdup(word));
	if (!fd_slash)
		return (get_path(word, data));
	path = search_exec(word, data->env);
	return (path);
}
