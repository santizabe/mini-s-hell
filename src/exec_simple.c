/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 19:59:33 by szapata-          #+#    #+#             */
/*   Updated: 2025/03/16 22:05:35 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static	void	set_redirs(t_cmd *cmds)
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
		set_redirs(cmds);
		execve(path, argv, data->env);
		perror("execve");
	}
	else
		waitpid(pid, NULL, 0);
	return (1);
}

int	execute_cmd(t_cmd *cmds, t_data *data)
{
	char	**argv;
	char	*path;

	path = search_path(cmds->w_lst->content, data->env);
	if (!path)
		return (-1);
	argv = set_argv(cmds->w_lst);
	if (!ft_isbuiltin(argv[0]))
		exec_child(path, argv, cmds, data);
	// else
	// 	main_builtin()
	free(argv);
	free(path);
	return (0);
}
