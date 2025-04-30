/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <fernando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:56:40 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/04/30 12:13:53 by fernando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief It search the actual env variable of PWD.
 */
void	built_pwd(t_data *data)
{
	char	*buffer;

	buffer = my_getenv("PWD", data->env);
	if (!buffer)
	{
		write(2, "pwd: PWD not set\n", 17);
		data->exit_status = EXIT_FAILURE;
	}
	if (buffer != NULL)
	{
		printf("%s\n", buffer);
		data->exit_status = 0;
	}
}

/**
 * @brief It does the same as echo but checks if it has missed the -n flag.
 */
void	built_echo(t_cmd cmd_lst, t_data *data)
{
	int		flag;

	flag = 0;
	if (cmd_lst.w_lst->next)
	{
		cmd_lst.w_lst = cmd_lst.w_lst->next;
		if (!ft_strncmp("-n", cmd_lst.w_lst->content, ft_strlen("-n")))
		{
			cmd_lst.w_lst = cmd_lst.w_lst->next;
			flag = 1;
		}
		while (cmd_lst.w_lst)
		{
			ft_putstr_fd(cmd_lst.w_lst->content, 1);
			cmd_lst.w_lst = cmd_lst.w_lst->next;
			if (cmd_lst.w_lst)
				ft_putchar_fd(' ', 1);
		}
	}
	if (!flag)
		ft_putstr_fd("\n", 1);
	data->exit_status = 0;
}

/**
 * @brief prints all the envirinements variables
 */
void	built_env(t_cmd *cmd_lst, t_data *data)
{
	if (cmd_lst->w_lst->next != NULL)
	{
		ft_putstr_fd("env: too much parameters\n", 2);
		data->exit_status = 127;
		return ;
	}
	while (*(data->env))
	{
		ft_putstr_fd(*(data->env), 1);
		write(1, "\n", 1);
		(data->env)++;
	}
}

/**
 * @brief frees all the memory and exit with a code or with 0
 * if there is't any argument
 */
void	built_exit(t_cmd *cmd_lst, t_data *data)
{
	int	num;

	ft_putstr_fd("exit\n", 2);
	if (cmd_lst->w_lst->next == NULL)
	{
		free_data(data, cmd_lst, 1);
		exit(data->exit_status);
	}
	else
	{
		if (!ft_isnum((char *)cmd_lst->w_lst->next->content))
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd((char *)cmd_lst->w_lst->next->content, 2);
			ft_putstr_fd(": number argument required\n", 2);
			free_data(data, cmd_lst, 1);
			exit(2);
		}
		num = ft_atoi(cmd_lst->w_lst->next->content);
		free_data(data, cmd_lst, 1);
		exit(num);
	}
}

/**
 * @brief It checks which built command is sent and calls the function that
 * executes that command.
 * 
 * @param cmd_lst is the command list that is given in the input
 * @param data value of the global program data
*/
void	main_builtin(t_cmd *cmd_lst, t_data *data)
{
	char	*cmd;

	if (cmd_lst->w_lst == NULL)
	{
		write(2, "Memory error\n", 13);
		free_data(data, cmd_lst, 1);
		exit(-1);
	}
	cmd = cmd_lst->w_lst->content;
	if (!ft_strncmp(cmd, "cd", ft_strlen("cd")))
		built_cd(cmd_lst, data);
	else if (!ft_strncmp(cmd, "exit", ft_strlen("exit")))
		built_exit(cmd_lst, data);
	else if (!ft_strncmp(cmd, "echo", ft_strlen("echo")))
		built_echo(*cmd_lst, data);
	else if (!ft_strncmp(cmd, "pwd", ft_strlen("pwd")))
		built_pwd(data);
	else if (!ft_strncmp(cmd, "env", ft_strlen("env")))
		built_env(cmd_lst, data);
	else if (!ft_strncmp(cmd, "export", ft_strlen("export")))
		built_export(*cmd_lst, data);
	else if (!ft_strncmp(cmd, "unset", ft_strlen("unset")))
		built_unset(*cmd_lst, data);
}
