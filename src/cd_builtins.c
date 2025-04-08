/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <fernando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:29:26 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/04/08 14:56:19 by fernando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	manage_pp(char *path, char *pwd, int i)
{
	int	cntp;
	int	len;

	cntp = 0;
	len = ft_strlen(pwd) - 1;
	while (path[i] && path[i + 1] && !ft_strncmp(&path[i],"..", 2))
	{
		cntp++;
		i += 2;
		if (path[i] == '/')
			i++;
	}
	while (pwd[len] && cntp > 0)
	{
		if (pwd[len] == '/' && pwd[len + 1] != '\0')
		{
			pwd[len] = '\0';
			cntp--;
		}
		len--;
	}
	if (pwd[len] == '\0' && cntp > 0)
		return (-1);
	return (i);
}

char	*ft_strjoin3(char *s1, char *s2, int b1, int b2)
{
	char	*res;

	if (!s1 || !s2)
		return NULL;
	
	res = ft_strjoin2(s1, s2);
	if (!res)
		return NULL;
	if (b1)
		free(s1);
	if (b2)
		free(s2);
	return (res);
}

char	*rebuild_path(char *path, char *pwd)
{
	int		i;
	char	*res;
	
	i = 0;
	while (!ft_strncmp(&path[i], "./", 2))
		i += 2;
	if (i > 0)
	{
		path = &path[i];
		i = 0;
	}
	i = manage_pp(path, pwd, i);
	if (i < 0)
	{
		free(pwd);
		return (NULL);
	}
	res = pwd;
	if (pwd[ft_strlen(pwd) - 1] != '/')
		res = ft_strjoin3(res, "/", 1, 0);
	if (path[i] && ft_isalnum(path[i]))
		res = ft_strjoin3(res, ft_strdup(path + i), 1, 1);
	return (res);
}

int	built_cd_path(char *path, char **env)
{
	int	err;
	char	*pwd;
	char	*new_path;
	
	pwd = my_getenv("PWD", env);
	if (!pwd)
	{
		ft_putstr_fd("cd: '", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("': PWD not set", 2);
		return (0);
	}
	new_path = rebuild_path(path, ft_strdup(pwd));
	if (!new_path)
		return (-1);
	err = chdir(new_path);
	if(!change_values_env("OLDPWD", pwd, env))
	{
		ft_export("OLDPWD", pwd, env);
	}
	change_values_env("PWD", new_path, env);
	free(new_path);
	return (err);
}

int	built_cd_old(char **env)
{
	int		err;
	char	*pwd;
	char	*old;
	
	pwd = ft_strdup(my_getenv("PWD", env));
	if (!pwd)
	{
		ft_putstr_fd("cd: '-': PWD not set", 2);
		return (0);
	}
	old = my_getenv("OLDPWD", env);
	if (!old)
	{
		ft_putstr_fd("cd: '-': OLDPWD not set", 2);
		return (0);
	}
	err = chdir(old);
    change_values_env("PWD", old, env);
	if(!change_values_env("OLDPWD", pwd, env))
	{
        ft_export("OLDPWD", pwd, env);
	}
	free(pwd);
	return(err);
}

int	built_cd_home(char **env)
{
	char	*pwd;
	char	*next;
	int		err;
	
	pwd = my_getenv("PWD", env);
	if (!pwd)
	{
		ft_putstr_fd("cd: PWD not set", 2);
		return (0);
	}
	next = my_getenv("HOME", env);
	if (!next)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		free(pwd);
		return (0);
	}
	err = chdir(next);
	if(!change_values_env("OLDPWD", pwd, env))
	{
		ft_export("OLDPWD", pwd, env);
	}
	change_values_env("PWD", next, env);
	return(err);
}

/**
 * @brief Handles the 'cd' shell builtin command (change directory).
 * 
 * Changes the current directory based on the provided arguments:
 * 
 * - If no argument, moves to the home directory (`built_cd_home`).
 * 
 * - If argument is "-", moves to the previous directory (`built_cd_old`).
 * 
 * - Otherwise, moves to the specified path (`built_cd_path`).
 * 
 * 
 * @param cmd_lst Command structure containing the argument (if any).
 * @param data Shell data structure holding environment variables.
 */
void	built_cd(t_cmd *cmd_lst, t_data *data)
{
	int		err;
	
	if (cmd_lst->w_lst->next == NULL)
		err = built_cd_home(data->env);
	else
	{
		if (!ft_strncmp(cmd_lst->w_lst->next->content, "-", 1))
			err = built_cd_old(data->env);
		else
			err = built_cd_path(cmd_lst->w_lst->next->content, data->env);
	}
	if (err)
	{
		ft_putstr_fd("Error path '", 2);
		ft_putstr_fd(cmd_lst->w_lst->next->content, 2);
		ft_putstr_fd("' does not exists\n", 2);
	}
}
