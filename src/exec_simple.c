/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 19:59:33 by szapata-          #+#    #+#             */
/*   Updated: 2025/05/06 19:18:10 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_redirs_simple(t_cmd *cmds)
{
	int	in_fd;
	int	out_fd;

	in_fd = 0;
	out_fd = 1;
	if (cmds->in_redir)
		in_fd = read_here_docs(cmds->in_redir);
	if (cmds->lst_order && check_files(cmds->lst_order))
		exit(EXIT_FAILURE);
	if (!in_fd && cmds->in_redir)
		in_fd = open_infile(cmds->in_redir);
	out_fd = open_outfiles(cmds->out_redir);
	if (dup2(in_fd, STDIN_FILENO) == -1 || dup2(out_fd, STDOUT_FILENO) == -1)
		print_err("dup2");
	if (in_fd > 2)
		close(in_fd);
	if (out_fd > 2)
		close(out_fd);
}

int	exec_child(char *path, char **argv, t_cmd *cmds, t_data *data)
{
	int	pid;

	pid = fork();
	if (pid == -1 && print_err("fork"))
		return (-1);
	else if (!pid)
	{
		signal(SIGINT, SIG_DFL);
		set_redirs_simple(cmds);
		if (cmds->w_lst)
		{
			execve(path, argv, data->env);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	else
		waitpid(pid, &data->exit_status, 0);
	return (1);
}

int	execute_cmd(t_cmd *cmds, t_data *data)
{
	char	**argv;
	char	*path;
	char	*aux;

	path = NULL;
	if (cmds->w_lst)
		path = search_path(cmds->w_lst->content, data);
	if (!path && cmds->w_lst)
		return (-1);
	argv = set_argv(cmds->w_lst);
	aux = NULL;
	if (argv)
		aux = *argv;
	if (!ft_isbuiltin(aux))
		exec_child(path, argv, cmds, data);
	else
		main_builtin(cmds, data);
	free(argv);
	free(path);
	return (0);
}
