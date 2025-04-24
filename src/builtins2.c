/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <fernando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:34:54 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/04/24 15:36:57 by fernando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	built_unset_aux(char *variable, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], variable, ft_strlen(variable))
			&& env[i][ft_strlen(variable)] == '=')
		{
			free(env[i]);
			env[i] = NULL;
			while (env[i + 1])
			{
				env[i] = env[i + 1];
				i++;
			}
			env[i] = NULL;
			break ;
		}
		i++;
	}
}

/**
 * @brief Removes environment variables specified in the command.
 * 
 * Iterates through command arguments and removes each variable from the 
 * environment
 * 
 * if it exists, uses helper function built_unset_aux() to perform the removal.
 * 
 * @param cmd_lst Command structure containing variables to unset.
 * @param env Environment variables array (modified in place).
 */
void	built_unset(t_cmd cmd_lst, char **env)
{
	char	*variable;

	while (cmd_lst.w_lst->next)
	{
		cmd_lst.w_lst = cmd_lst.w_lst->next;
		variable = cmd_lst.w_lst->content;
		if (my_getenv(variable, env))
			built_unset_aux(variable, env);
	}
}

/**
 * @brief function that handle the execution of the export command
 *
 * @param cmd_lst is the command list that is given in the input
 * @param data value of the global program data
*/
void	built_export(t_cmd cmd_lst, t_data *data)
{
	if (!cmd_lst.w_lst->next)
		return ;
	while (cmd_lst.w_lst->next)
	{
		built_export_aux(cmd_lst, data);
		cmd_lst.w_lst = cmd_lst.w_lst->next;
	}
}
