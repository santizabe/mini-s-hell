/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:05:41 by szapata-          #+#    #+#             */
/*   Updated: 2025/03/17 16:44:20 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_files(t_list *redir_lst)
{
	t_redir	*redir;

	redir = NULL;
	while (redir_lst)
	{
		redir = (t_redir *)redir_lst->content;
		if (redir->mode == (O_RDONLY))
		{
			if (access(redir->file, R_OK) && print_err(redir->file))
				return (-1);
		}
		else if (redir->mode == (O_RDWR | O_CREAT | O_TRUNC)
			|| redir->mode == (O_WRONLY | O_CREAT | O_APPEND))
			if ((!access(redir->file, F_OK)
					&& access(redir->file, W_OK)) && print_err(redir->file))
				return (-1);
		redir_lst = redir_lst->next;
	}
	return (0);
}

int	open_outfiles(t_list *f_lst)
{
	int		fd;
	t_redir	*redir;

	fd = 1;
	while (f_lst)
	{
		redir = (t_redir *)f_lst->content;
		fd = open(redir->file, redir->mode, 0777);
		if (fd == -1 && print_err("open"))
			return (-1);
		if (!(f_lst->next))
			break ;
		close(fd);
	}
	return (fd);
}

int	read_here_doc(char *limit)
{
	char	*b;
	pid_t	pid;
	int		fd[2];

	pipe(fd);
	pid = fork();
	if (!pid)
	{
		close(fd[0]);
		b = get_next_line(0);
		while (b && ft_strncmp(b, limit, ft_strlen(b) - 1))
		{
			write(fd[1], b, ft_strlen(b));
			free(b);
			b = get_next_line(0);
		}
		close(fd[1]);
		exit(EXIT_SUCCESS);
	}
	close(fd[1]);
	wait(NULL);
	return (fd[0]);
}

int	read_here_docs(t_list *in_lst)
{
	t_redir	*redir;
	int		fd;

	fd = 0;
	while (in_lst)
	{
		redir = (t_redir *)in_lst->content;
		if (redir->mode == -1)
			fd = read_here_doc(redir->file);
		if (in_lst->next)
			close(fd);
		in_lst = in_lst->next;
	}
	return (fd);
}

int	open_infile(t_list *f_lst)
{
	t_redir	*redir;
	int		fd;

	redir = NULL;
	fd = 0;
	while (f_lst && f_lst->next)
		f_lst = f_lst->next;
	if (f_lst)
	{
		redir = (t_redir *)f_lst->content;
		fd = open(redir->file, redir->mode);
		if (fd == -1)
			print_err(redir->file);
	}
	return (fd);
}
