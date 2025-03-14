/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:58:46 by szapata-          #+#    #+#             */
/*   Updated: 2025/03/12 19:56:30 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	print_err(char *str)
{
	ft_putstr_fd("Minishell: ", STDOUT_FILENO);
	perror(str);
	return (1);
}

void	set_argv(t_list *args, char **argv)
{
	while (args)
	{
		*argv++ = args->content;
		args = args->next;
	}
}

void	print_args_path(char *path, t_list *list, char **env)
{
	printf("path: %s\nArgs: ", path);
	while (list)
	{
		printf("%s, ", (char *)list->content);
			list = list->next;
	}
	while (env && *env)
	{
		printf("%s\n", *env);
		env++;
	}
	printf("\n");
}

void	exec_builtin(char **argv, char **env)
{
	// int	cmd_len;

	// cmd_len = ft_strlen(argv[0]);
	// if (!ft_strncmp(argv[0], "cd", cmd_len))
	// 	cd_builtin(argv, env);
	// else if (!ft_strncmp(argv[0], "pwd", cmd_len))
	// 	pwd_builtin(argv, env);
	// else if (!ft_strncmp(argv[0], "env", cmd_len))
	// 	env_builtin(argv, env);
	// else if (!ft_strncmp(argv[0], "echo", cmd_len))
	// 	env_builtin(argv, env);
	// else if (!ft_strncmp(argv[0], "export", cmd_len))
	// 	export_builtin(argv, env);
	// else if (!ft_strncmp(argv[0], "unset", cmd_len))
	// 	unset_builtin(argv, env);
	// else
	// 	exit_builtin(argv, env);
	env++;
	printf("%s is a builtin\n", argv[0]);
}

int	exec_child(char *path, char **argv, char **env)
{
	int	pid;

	pid = fork();
	if (pid == -1 && print_err("fork"))
		return (-1);
	else if (!pid)
	{
		execve(path, argv, env);
		perror("execve");
	}
	else
		waitpid(pid, NULL, 0);
	return (1);
}

int	execute_cmd(char *path, t_list *args, char **env)
{
	char	**argv;
	int		lstsize;

	if (!path)
		return (-1);
	lstsize = ft_lstsize(args);
	argv = NULL;
	if (lstsize)
		argv = (char **)malloc(sizeof(char *) * (lstsize + 1));
	argv[lstsize] = NULL;
	//get_cmd(args);
	set_argv(args, argv);
	if (ft_isbuiltin(argv[0]))
		exec_builtin(argv, env);
	else
		exec_child(path, argv, env);
	free(argv);
	return (0);
}

int		exec_simple(t_cmd *cmd_lst, char **env)
{
	int		in_fd;
	int		out_fd;
	char	*path;

	out_fd = 1;
	in_fd = read_here_docs(cmd_lst->in_redir);
	if (!check_files(cmd_lst->lst_order))
	{
		if (!in_fd && cmd_lst->in_redir)
			in_fd = open_infile(cmd_lst->in_redir);
		out_fd = open_outfiles(cmd_lst->out_redir);
	}
	path = search_path(cmd_lst->w_lst->content, env);
	if ((dup2(in_fd, STDIN_FILENO) == -1
		|| dup2(out_fd, STDOUT_FILENO) == -1) && print_err("dup2"))
		return (-1);
	execute_cmd(path, cmd_lst->w_lst, env);
	free(path);
	if (in_fd > 2)
		close(in_fd);
	if (out_fd > 2)
		close(out_fd);
	return (0);
}

void	reset_fds(int in, int out)
{
	int	tmp;

	tmp = dup2(in, STDIN_FILENO);
	if (tmp == -1)
		print_err("dup2");
	tmp = dup2(out, STDOUT_FILENO);
	if (tmp == -1)
		print_err("dup2");
	unlink(".msh_here");
	close(in);
	close(out);
}

// int	set_redir(t_cmd *cmd)
// {
// 	int	in;
// 	int	out;

// 	in_fd = read_here_docs(cmd_lst->in_redir);
// 	if (!check_files(cmd_lst->lst_order))
// 	{
// 		if (!in_fd && cmd_lst->in_redir)
// 			in_fd = open_infile(cmd_lst->in_redir);
// 		out_fd = open_outfiles(cmd_lst->out_redir);
// 	}
// }

// int	exec_multiple(t_cmd *cmd_lst, char **env)
// {
// 	int	pipe_fd[2];

// 	if (pipe(pipe_fd) == -1 && print_err("pipe"));
// 		return (-1);
// 	dup2(pipe_fd[1], STDIN_FILENO);
// 	while(cmd_lst)
// 	{
// 		if (set_redir(cmd_lst))
// 			exec_cmd();
// 		cmd_lst = cmd_lst->next;
// 		dup2(pipe_fd[0], STDIN_FILENO);
// 		dup2(pipe_fd[1], STDOUT_FILENO);
// 	}
// }

void	ft_execute(t_cmd *cmd_lst, char **env)
{
	int	save_in_out[2];

	env++;
	save_in_out[0] = dup(STDIN_FILENO); // saves stdin fd
	save_in_out[1] = dup(STDOUT_FILENO); // saves stdout fd
	if ((save_in_out[0] == -1 || save_in_out[1] == -1)
		&& print_err("dup"))
		return ;
	if (!(cmd_lst->next))
		exec_simple(cmd_lst, env);
	// else
	// 	exec_multiple(cmd_lst, env);
	reset_fds(save_in_out[0], save_in_out[1]);
}
