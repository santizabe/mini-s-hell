/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <fernando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:56:40 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/03/26 12:18:27 by fernando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_isnum(char *str)
{
	int i;
	
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while(str[i])
	{
		if (!ft_isdigit(str[i++]))
			return (0);
	}
	return (1);
}

int	change_values_env(char *name, char *str, char **env)
{
	int		strlen;
	char	*new_env;

	strlen = ft_strlen(name);
	while(*env)
	{
		if (!ft_strncmp(name, *env, strlen) && (*env)[strlen] == '=')
		{
			new_env = (char *)malloc((strlen + ft_strlen(str) + 2)  * sizeof(char));
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

void	built_cd(t_cmd *cmd_lst, t_data *data)
{
	int		err;
	char	*pwd;
	char	*next;
	
	if (cmd_lst->w_lst->next == NULL)
	{
		pwd = my_getenv("PWD", data->env);
		if (!pwd)
		{
			//export pwd gentev(PWD)
		}
		next = my_getenv("HOME", data->env);
		if (!next)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			free(pwd);
			return;
		}
		err = chdir(next);
		change_values_env("PWD", next, data->env);
		if(change_values_env("OLDPWD", pwd, data->env))
		{
			//export OLDPWD pwd
		}
	}
	else
	{
		
		err = chdir(cmd_lst->w_lst->next->content);
	}
	if (err)
		ft_putstr_fd("Error en chdir\n", 2);
}

void	built_pwd(t_data *data)
{
	char	*buffer;
	
	buffer = my_getenv("PWD", data->env);
	if (!buffer)
	{
		//export pwd gentev(pwd)
	}
	if (buffer != NULL)
        printf("%s\n", buffer);
}

void	built_echo(t_cmd cmd_lst)
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
}

void	built_env(t_cmd *cmd_lst, char **env)
{
	if (cmd_lst->w_lst->next != NULL)
	{
		ft_putstr_fd("env: too much parameters\n", 2);
		return ;
	}
	while(*env)
	{
		ft_putstr_fd(*env, 1);
		write(1, "\n", 1);
		env++;
	}
}

void	built_exit(t_cmd *cmd_lst, t_data *data)
{
	int	num;

	ft_putstr_fd("exit\n", 2);
	if (cmd_lst->w_lst->next == NULL)
	{
		free_data(data, cmd_lst, 1);
		exit(0);
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
 * @brief copies all the string `str` until the int `c` match with 
 * any character of str
 * 
 * @param str is the string that is going to be copied
 * @param c is the character search
*/
char *cpy_first_part_env_var(char *str, int c)
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
		change_values_env(value, variable, data->env);
	else if (variable != NULL)
		data->env = ft_export(value, variable, data->env);
	free(value);
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
		ft_putstr_fd("Error: export: no arguments received\n", 2);
		return ;
	}
	while (cmd_lst.w_lst->next)
	{
		built_export_aux(cmd_lst, data);
		cmd_lst.w_lst = cmd_lst.w_lst->next;
	}
}

void	built_unset(t_cmd *cmd_lst, t_data *data)
{
	(void)cmd_lst;
	(void)data;
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
		write(1, "La lista es nula\n", 17);
		free_data(data, cmd_lst, 1);
		exit(-1);
	}
	cmd = cmd_lst->w_lst->content;
	if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
		built_cd(cmd_lst, data);
	else if (!ft_strncmp(cmd, "exit", ft_strlen(cmd)))
		built_exit(cmd_lst, data);
	else if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)))
		built_echo(*cmd_lst);
	else if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
		built_pwd(data);
	else if (!ft_strncmp(cmd, "env", ft_strlen(cmd)))
		built_env(cmd_lst, data->env);
	else if (!ft_strncmp(cmd, "export", ft_strlen(cmd)))
		built_export(*cmd_lst, data);
	else if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
		built_unset(cmd_lst, data);
}
