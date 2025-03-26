/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <fernando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:19:29 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/03/26 12:21:19 by fernando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	{
		write(2, "Error allocating memory", 23);
		return (NULL);
	}
	j = 0;
	while (j < i)
		new_env[j] = env[j++];
	new_env[j] = ft_strdup(env_var);
	if (!new_env[j])
	{
		write(2, "Error allocating memory", 23);
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
	int		strlen_value;

	strlen_var = ft_strlen(var);
	strlen_value = ft_strlen(value);
	env_var = (char *)malloc((strlen_var + strlen_value + 2)  * sizeof(char));
	if (!env_var)
		return (NULL);
	ft_memcpy(env_var, var, strlen_var);
	env_var[strlen_var] = '=';
	ft_memcpy(env_var + strlen_var + 1, value, strlen_value + 1);
	new_env = create_new_env(env_var, env);
	if (!new_env)
		return (NULL);
	free_array(env);
	return(new_env);
}
