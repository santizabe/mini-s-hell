/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <fernando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:19:29 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/04/11 21:12:11 by fernando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Reconstructs an absolute path from relative components.  
 *  
 * @param path Relative path to process.  
 * @param pwd Current working directory (modified/freed if needed).  
 * @return Newly allocated absolute path, or NULL if invalid.
 */
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
	if (pwd[ft_strlen(pwd) - 1] != '/' && path[i] != '/')
		res = ft_strjoin3(res, "/", 1, 0);
	if (path[i])
		res = ft_strjoin3(res, ft_strdup(path + i), 1, 1);
	return (res);
}

/**
 * @brief copies all the string `str` until the int `c` match with 
 * any character of str, axiliar function user for export.
 * 
 * @param str is the string that is going to be copied
 * @param c is the character search
*/
char	*cpy_first_part_env_var(char *str, int c)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	res = (char *)malloc((i + 1) * sizeof(char));
	if (!res)
		return (0);
	j = 0;
	while (j < i)
	{
		res[j] = str[j];
		j++;
	}
	res[j] = '\0';
	return (res);
}

/**
 * @brief Axuliar function for the main export builtin function
*/
void	built_export_aux(t_cmd cmd_lst, t_data *data)
{
	char	*value;
	char	*variable;
	char	*str;

	str = cmd_lst.w_lst->next->content;
	value = cpy_first_part_env_var(str, '=');
	if (!(value) || (value[0] == '\0'))
	{
		ft_putstr_fd("export: '", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		free(value);
		return ;
	}
	variable = ft_strchr(str, '=');
	if (variable != NULL && my_getenv(value, data->env))
		change_values_env(value, variable + 1, data->env);
	else if (variable != NULL)
		data->env = ft_export(value, variable + 1, data->env);
	free(value);
}

/**
 * @brief It creates a new array with a new env variable `env_var` added.
 *
 * @param env_var the new environement variable (format "KEY=VALUE").
 * @param env the actual enviorement that is going to change (NULL-terminated
 *  array of strings).
 * 
 * @return I A new NULL-terminated array containing all original variables
 *         plus `env_var`. Returns NULL on error.
*/
char	**create_new_env(const char *env_var, char **env)
{
	char	**new_env;
	int		i;
	int		j;

	i = 0;
	while (env[i])
		i++;
	new_env = (char **)malloc((i + 2) * sizeof(char *));
	if (new_env == NULL)
		return (NULL);
	j = 0;
	while (j < i)
	{
		new_env[j] = env[j];
		j++;
	}
	new_env[j] = ft_strdup(env_var);
	if (!new_env[j])
	{
		free(new_env);
		return (NULL);
	}
	new_env[j + 1] = NULL;
	return (new_env);
}

/**
 * @brief It creates a new environment variable
 *
 * @param var is the name of the new variable that you want to put in env
 * @param value is the value of var
 * @param env the enviorement where we have to add the new variable
*/
char	**ft_export(char *var, char *value, char **env)
{
	char	*env_var;
	char	**new_env;
	int		strlen_var;

	strlen_var = ft_strlen(var);
	env_var = (char *)malloc((strlen_var + ft_strlen(value) + 2)
			* sizeof(char));
	if (!env_var)
	{
		write(2, "Error allocating memory", 23);
		return (NULL);
	}
	ft_memcpy(env_var, var, strlen_var);
	env_var[strlen_var] = '=';
	ft_memcpy(env_var + strlen_var + 1, value, ft_strlen(value) + 1);
	new_env = create_new_env(env_var, env);
	if (!new_env)
	{
		free(env_var);
		write(2, "Error allocating memory", 23);
		return (NULL);
	}
	free(env);
	free(env_var);
	return (new_env);
}
