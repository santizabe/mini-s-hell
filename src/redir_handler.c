/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:05:41 by szapata-          #+#    #+#             */
/*   Updated: 2025/03/06 13:09:21 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	print_err(char *str)
{
	ft_putstr_fd("Minishell: ", STDOUT_FILENO);
	perror(str);
	return (1);
}

int		check_files(t_list *redir_lst)
{
	t_redir	*redir;

	redir = NULL;
	while (redir_lst)
	{
		redir = (t_redir *)redir_lst->content;
		if (redir->mode == O_RDONLY)
			if (access(redir->file, R_OK) && print_err(redir->file))
				return (-1);
		else if (redir->mode == O_RDWR | O_CREAT | O_TRUNC
			|| redir->mode == O_WRONLY | O_CREAT | O_APPEND)
		{
			if ((!access(redir->file, F_OK)
				&& access(redir->file, W_OK)) && print_err(redir->file))
				return (-1);
		}
		redir_lst = redir_lst->next;
	}
	return (0);
}

int		open_outfiles(t_list *f_lst)
{
	int		fd;
	t_redir	*redir;

	fd = 1;
	while (f_lst)
	{
		redir = (t_redir *)f_lst->content;
		if (redir->mode == (O_RDWR | O_CREAT | O_TRUNC)
			|| redir->mode == (O_RDWR | O_CREAT | O_APPEND))
			fd = open(redir->file, redir->mode, 0777);
		else if (redir->mode == O_RDONLY)
			fd = open(redir->file, redir->mode);
		if (fd == -1 && print_err("open"))
			return (-1);
		if (!(f_lst->next))
			break ;
		close(fd);
	}
	return (fd);
}

int		read_here_doc(char *limit, t_list *node)
{
	int		fd;
	char	*line;
	
	fd = open(".msh_here", O_RDWR | O_CREAT, 0777);
	if (fd == -1 && print_err("open"));
		return (-1);
	while (1)
	{
		line = get_next_line(0);
		ft_putstr_fd(line, fd);
		if (!ft_strncmp(line, limit, ft_strlen(line)))
			break ;
	}
	if (node)
	{
		close(fd);
		unlink(".msh_here");
		fd = 0;
	}
	return (fd);
}

int		read_here_docs(t_list *in_lst)
{
	t_redir	*redir;
	char	*line;
	int		fd;

	fd = 0;
	while (in_lst)
	{
		redir = (t_redir *)in_lst->content;
		if (redir->mode == -1)
			fd = read_here_doc(redir->file, in_lst->next);
		in_lst = in_lst->next;
	}
	return (fd);
}

int		open_infile(t_list *f_lst)
{
	t_redir	*redir;
	int		fd;

	fd = read_here_docs(f_lst);
	if (fd == -1)
		return (fd);
	if (check_files(f_lst))
	{
		if (fd > 2 && close(fd))
			return (-1);
	}
	else if (fd > 2)
		return (fd);
	while (!fd && f_lst)
		f_lst = f_lst->next;
	redir = (t_redir *)f_lst->content;
	fd = open(redir->file, redir->mode);
	if (fd == -1)
		print_err(redir->file);
	return (fd);
}