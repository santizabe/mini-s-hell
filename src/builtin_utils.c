/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <fernando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:10:12 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/04/11 20:58:25 by fernando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Processes ".." in a path and adjusts the pwd accordingly.  
 *  
 * @param path Path to process.  
 * @param pwd Current working directory (modified in place).  
 * @param i Starting index in path.  
 * @return New index after processing, or -1 if path escapes root.  
 */
int	manage_pp(char *path, char *pwd, int i)
{
	int	cntp;
	int	len;

	cntp = 0;
	len = ft_strlen(pwd) - 1;
	while (path[i] && path[i + 1] && !ft_strncmp(&path[i], "..", 2))
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

/**
 * @brief Checks if a string represents a valid integer number.
 * 
 * @param str String to check (e.g., "-123", "+456", "789").
 * @return 1 if the string is a valid integer (optional sign + digits), 
 * 0 otherwise.
 */
int	ft_isnum(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i++]))
			return (0);
	}
	return (1);
}

/**
 * @brief Updates an environment variable's value in the given environment array.
 * 
 * @param name Name of the variable to update (e.g., "PATH").
 * @param str New value to assign (e.g., "/usr/local/bin").
 * @param env Environment array (NULL-terminated strings, e.g., `environ`).
 * @return 1 if the variable was found and updated, 0 otherwise.
 */
int	change_values_env(char *name, char *str, char **env)
{
	int		strlen;
	char	*new_env;

	strlen = ft_strlen(name);
	while (*env)
	{
		if (!ft_strncmp(name, *env, strlen) && (*env)[strlen] == '=')
		{
			new_env = (char *)malloc((strlen + ft_strlen(str) + 2)
					* sizeof(char));
			if (!new_env)
				return (0);
			ft_memcpy(new_env, name, strlen);
			new_env[strlen] = '=';
			ft_memcpy(new_env + strlen + 1, str, ft_strlen(str) + 1);
			free(*env);
			*env = new_env;
			return (1);
		}
		env++;
	}
	return (0);
}

/**
 * Implementation of strjoin only used to free the memory leaked on cd
 */
char	*ft_strjoin3(char *s1, char *s2, int b1, int b2)
{
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	res = ft_strjoin2(s1, s2);
	if (!res)
		return (NULL);
	if (b1)
		free(s1);
	if (b2)
		free(s2);
	return (res);
}
