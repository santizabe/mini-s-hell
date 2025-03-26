/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fosuna-g <fosuna-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:29:26 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/03/26 20:45:18 by fosuna-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	if(change_values_env("OLDPWD", pwd, env))
	{
		ft_export("OLDPWD", pwd, env);
	}
	change_values_env("PWD", next, env);
	return(err);
}


int	built_cd_path(char *path, char **env)
{
	int	err;
	char	*pwd;
	
	pwd = my_getenv("PWD", env);
	if (!pwd)
	{
		ft_putstr_fd("cd: '", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("': PWD not set", 2);
		return (0);
	}
	err = chdir(path);
	if(change_values_env("OLDPWD", pwd, env))
	{
		ft_export("OLDPWD", pwd, env);
	}
	change_values_env("PWD", path, env);
	return (err);
}

int	built_cd_old(char **env)
{
	int		err;
	char	*pwd;
	char	*old;
	
	pwd = my_getenv("PWD", env);
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
	if(change_values_env("OLDPWD", pwd, env))
	{
        ft_export("OLDPWD", pwd, env);
	}
	return(err);
}

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
