/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <fernando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:29:26 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/05/08 13:06:01 by fernando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**built_cd_path(char *path, char **env, int *err)
{
	char	*pwd;
	char	*new_path;

	pwd = my_getenv("PWD", env);
	if (!pwd)
	{
		ft_putstr_fd("cd: '", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("': PWD not set\n", 2);
		*err = 1;
		return (env);
	}
	*err = chdir(path);
	if (!*err)
	{
		new_path = getcwd(NULL, 0);
		if (!*err && !change_values_env("OLDPWD", pwd, env))
			env = ft_export("OLDPWD", pwd, env);
		change_values_env("PWD", new_path, env);
		free(new_path);
	}
	return (env);
}

char	**built_cd_old(char **env, int *err)
{
	char	*pwd;
	char	*old;

	pwd = ft_strdup(my_getenv("PWD", env));
	if (!pwd)
	{
		ft_putstr_fd("cd: '-': PWD not set\n", 2);
		*err = 1;
		return (env);
	}
	old = my_getenv("OLDPWD", env);
	if (!old)
	{
		ft_putstr_fd("cd: '-': OLDPWD not set\n", 2);
		*err = 1;
		return (env);
	}
	*err = chdir(old);
	if (!*err)
		change_values_env("PWD", old, env);
	if (!*err && !change_values_env("OLDPWD", pwd, env))
		env = ft_export("OLDPWD", pwd, env);
	free(pwd);
	return (env);
}

char	**built_cd_home(char **env, int *err)
{
	char	*pwd;
	char	*next;

	pwd = my_getenv("PWD", env);
	if (!pwd)
	{
		ft_putstr_fd("cd: PWD not set\n", 2);
		*err = 1;
		return (env);
	}
	next = my_getenv("HOME", env);
	if (!next)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		*err = 1;
		return (env);
	}
	*err = chdir(next);
	if (!*err && !change_values_env("OLDPWD", pwd, env))
		env = ft_export("OLDPWD", pwd, env);
	if (!*err)
		change_values_env("PWD", next, env);
	return (env);
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
 * - If argument starts with '/', treats it as an absolute path
 *  (`built_cd_root`).
 * 
 * - Otherwise, treats it as a relative path (`built_cd_path`).
 *  
 * @param cmd_lst Command structure containing the argument (if any).  
 * @param data Shell data structure holding environment variables.  
 */

void	built_cd(t_cmd *cmd_lst, t_data *data)
{
	int	err;

	err = 0;
	if (cmd_lst->w_lst->next == NULL)
		data->env = built_cd_home(data->env, &err);
	else if (!ft_strncmp(cmd_lst->w_lst->next->content, "-", 1))
		data->env = built_cd_old(data->env, &err);
	else if (!cmd_lst->w_lst->next->next)
	{
		data->env = built_cd_path(cmd_lst->w_lst->next->content, data->env,
				&err);
	}
	else
		err = write(2, "cd: too many arguments\n", 23);
	data->exit_status = err;
	if (err < 0)
	{
		ft_putstr_fd("Error path '", 2);
		ft_putstr_fd(cmd_lst->w_lst->next->content, 2);
		ft_putstr_fd("' does not exists\n", 2);
		data->exit_status = 1;
	}
}
