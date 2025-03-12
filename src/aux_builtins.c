/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fosuna-g <fosuna-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:19:29 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/03/12 19:15:45 by fosuna-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**create_new_env(char *env_var, char **env)
{
	(void)env_var;
	return (env);
}

/**
 * @brief It do the same than the real function export
 *
 * @param var is the name of the new variable that you want to put in env
 * @param value is the value of var
 * @param env the enviorement where we have to add the new variable
*/
void	ft_export(char *var, char *value, char **env)
{
	char	*env_var;
	char	**new_env;
	int		strlen_var;
	int		strlen_value;

	strlen_var = ft_strlen(var);
	strlen_value = ft_strlen(value);
	env_var = (char *)malloc((strlen_var + strlen_value + 2)  * sizeof(char));
	if (!env_var)
		return ;
	ft_memcpy(env_var, var, strlen_var);
	env_var[strlen_var] = '=';
	ft_memcpy(env_var + strlen_var + 1, value, strlen_value + 1);
	new_env = create_new_env(env_var, env);
	if (!new_env)
		return ;
	double_free(env);
	env = new_env;
}
