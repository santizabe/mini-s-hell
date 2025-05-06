/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <fernando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:34:54 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/05/01 18:47:13 by fernando         ###   ########.fr       */
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
void	built_unset(t_cmd cmd_lst, t_data *data)
{
	char	*variable;

	while (cmd_lst.w_lst->next)
	{
		cmd_lst.w_lst = cmd_lst.w_lst->next;
		variable = cmd_lst.w_lst->content;
		if (my_getenv(variable, data->env))
			built_unset_aux(variable, data->env);
	}
	data->exit_status = 0;
}

void	copy_sorted(char **env, char **sort, int size)
{
	char	*tmp;
	int		i;
	int		j;

	i = -1;
	while (env[++i])
		sort[i] = env[i];
	j = 0;
	while (j < size)
	{
		i = 0;
		while (i < size - 1)
		{
			if (ft_strncmp(sort[i], sort[i + 1], ft_strlen(sort[i])) > 0)
			{
				tmp = sort[i];
				sort[i] = sort[i + 1];
				sort[i + 1] = tmp;
			}
			i++;
		}
		j++;
	}
}

int	export_print(char **env)
{
	char	**sort;
	char	**split;
	int		i;
	int		len;

	i = 0;
	len = d_ptrlen(env);
	sort = (char **)malloc((len + 1) * sizeof(char *));
	if (!sort)
		return (-1);
	sort[len] = NULL;
	copy_sorted(env, sort, len);
	while (sort[i])
	{
		split = ft_split(sort[i++], '=');
		if (!split)
			return (-1);
		if (split[1] == NULL)
			printf("declare -x %s=\"\"\n", split[0]);
		else
			printf("declare -x %s=\"%s\"\n", split[0], split[1]);
		free_array(split);
	}
	free(sort);
	return (0);
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
	{
		if (export_print(data->env)
			&& write(2, "Error: malloc\n", 14))
		{
			free_data(data, &cmd_lst, 1);
			exit(EXIT_FAILURE);
		}
		return ;
	}
	while (cmd_lst.w_lst->next)
	{
		built_export_aux(cmd_lst, data);
		cmd_lst.w_lst = cmd_lst.w_lst->next;
	}
}
