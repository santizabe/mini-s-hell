/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 19:57:33 by szapata-          #+#    #+#             */
/*   Updated: 2025/05/06 18:49:54 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	print_err(char *str)
{
	ft_putstr_fd("Minishell: ", STDOUT_FILENO);
	perror(str);
	return (1);
}

int	clo_exec(int pipefd[2], char **argv, char *path, int pid)
{
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	free(argv);
	free(path);
	return (pid);
}

int	close_multiple(int pipefd[2], int std_tmp[2])
{
	close(pipefd[1]);
	close(pipefd[0]);
	close (std_tmp[0]);
	close (std_tmp[1]);
	return (0);
}

char	**set_argv(t_list *args)
{
	int		lstsize;
	char	**argv;
	char	**tmp;

	if (!args)
		return (NULL);
	lstsize = ft_lstsize(args);
	argv = NULL;
	if (lstsize)
		argv = (char **)malloc(sizeof(char *) * (lstsize + 1));
	if (!argv)
		return (NULL);
	argv[lstsize] = NULL;
	tmp = argv;
	while (args)
	{
		*tmp++ = args->content;
		args = args->next;
	}
	return (argv);
}
