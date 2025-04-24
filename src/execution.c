/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:58:46 by szapata-          #+#    #+#             */
/*   Updated: 2025/04/24 18:13:33 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	set_redir(t_cmd *cmd_lst, int std_tmp[2])
{
	int	in_fd;
	int	out_fd;

	out_fd = STDOUT_FILENO;
	in_fd = 0;
	if (cmd_lst->in_redir && dup2(std_tmp[0], STDIN_FILENO) != -1)
		in_fd = read_here_docs(cmd_lst->in_redir);
	if (cmd_lst->lst_order && check_files(cmd_lst->lst_order))
		return (0);
	if (!in_fd && cmd_lst->in_redir)
		in_fd = open_infile(cmd_lst->in_redir);
	out_fd = open_outfiles(cmd_lst->out_redir);
	if (dup2(in_fd, 0) == -1 || dup2(out_fd, 1) == -1)
		print_err("dup2");
	if (in_fd > 2)
		close(in_fd);
	if (out_fd > 2)
		close(out_fd);
	return (0);
}

int	exec_cmd(t_cmd *cmd_lst, t_data *data, int std_tmp[2])
{
	int		pid;
	int		pipefd[2];
	char	**argv;
	char	*path;

	if (pipe(pipefd) == -1 && print_err("pipe"))
		return (-1);
	path = search_path(cmd_lst->w_lst->content, data);
	argv = set_argv(cmd_lst->w_lst);
	pid = fork();
	if (pid == -1 && print_err("fork"))
		return (-1);
	else if (!pid)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		if (!cmd_lst->next)
			dup2(std_tmp[1], STDOUT_FILENO);
		set_redir(cmd_lst, std_tmp);
		close_multiple(pipefd, std_tmp);
		exec_2(cmd_lst, data, path, argv);
	}
	clo_exec(pipefd, argv, path, pid);
	return (pid);
}

int	exec_multiple(t_cmd *cmd_lst, t_data *data)
{
	int	i;
	int	j;
	int	std_tmp[2];
	int	pid_arr[99];

	i = 0;
	std_tmp[0] = dup(STDIN_FILENO);
	std_tmp[1] = dup(STDOUT_FILENO);
	while (cmd_lst)
	{
		pid_arr[i++] = exec_cmd(cmd_lst, data, std_tmp);
		cmd_lst = cmd_lst->next;
	}
	j = 0;
	while (j <= i)
		if (pid_arr[j++] != -1)
			waitpid(pid_arr[j], &data->exit_status, 0);
	dup2(std_tmp[0], STDIN_FILENO);
	dup2(std_tmp[1], STDOUT_FILENO);
	if ((close(std_tmp[0]) || close(std_tmp[1]))
		&& print_err("close"))
		return (-1);
	return (0);
}

/**
 * @brief Executes either a single command or a pipeline from the command list.
 * 
 * @param cmd_lst Command list to execute (single command or pipeline).
 * @param data Shell data containing environment and state.
 * @note Automatically removes temporary here-doc file (.msh_here) after 
 * execution.
 */
void	ft_execute(t_cmd *cmd_lst, t_data *data)
{
	int	ret;

	ret = 0;
	g_exit_status = 1;
	if (!(cmd_lst->next))
		ret = execute_cmd(cmd_lst, data);
	else
		exec_multiple(cmd_lst, data);
	if (ret == 0)
	{
		if (WIFSIGNALED(data->exit_status))
			data->exit_status = 128 + WTERMSIG(data->exit_status);
		else if (WIFEXITED(data->exit_status))
			data->exit_status = WEXITSTATUS(data->exit_status);
	}
}
