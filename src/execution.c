/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:58:46 by szapata-          #+#    #+#             */
/*   Updated: 2025/03/05 11:15:09 by szapata-         ###   ########.fr       */
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
		redir_lst = redir_lst->next;
	}
	return (0);
}

int		exec_simple(t_cmd *cmd_lst)
{
	if (check_files(cmd_lst->in_redir))
		return (-1);
	ft_putstr_fd("All good\n", STDOUT_FILENO);
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
	close(in);
	close(out);
}

void	ft_execute(t_cmd *cmd_lst, char **env)
{
	int	save_in_out[2];

	env++;
	save_in_out[0] = dup(STDIN_FILENO); // saves stdin fd
	save_in_out[1] = dup(STDOUT_FILENO); // saves stdout fd
	if ((save_in_out[0] == -1 && print_err("dup"))
		|| (save_in_out[1] == -1 && print_err("dup")))
		return ;
	if (!(cmd_lst->next))
		exec_simple(cmd_lst);
	// else
	// 	exec_multiple(cmd_lst);
	reset_fds(save_in_out[0], save_in_out[1]);
}
