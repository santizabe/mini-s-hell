/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 22:03:04 by szapata-          #+#    #+#             */
/*   Updated: 2024/11/15 22:37:38 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	If a $ is found, it should expand the variable if
	not inside simple quotes
 */

// char	*ft_expand_word(char *str)
// {
// 	char	*exp;
// 	char	*s_q;
// 	char	*d_q;

// 	exp = ft_strchr(str, '$');
// 	if (!exp)
// 		return (str);
// 	s_q = ft_strchr(str, '\'');
// 	d_q = ft_strchr(str, '\"');
// 	if (s_q)
// }

char	*ft_join(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*var;

	s3++;
	tmp = s3;
	var = NULL;
	while (s3 && *s3 && ft_isalpha(*s3))
		s3++;
	while (s3 != tmp && ft_isalnum(*s3))
		s3++;
	tmp = ft_substr(tmp, 0, s3 - tmp);
	if (!tmp)
		return (NULL);
	var = getenv(tmp);
}

char	*ft_expand_word(char *str)
{
	char	*tmp;
	char	*res;
	char	q;

	tmp = str;
	q = 0;
	res = NULL;
	while (str && *str)
	{
		if (*str == '\"')
			++q;
		if (*str == '\'' && !(q % 2) && str++)
			while (*str && *str != '\'')
				str++;
		if (*str == '$')
		{
			res = ft_join(res, tmp, str);
			if (!res)
				return (NULL);
		}
		str++;
	}
	res = str + 1;

	return (res);
}

int	ft_args_expand(t_list *lst)
{
	char	*str;

	str = NULL;
	while (lst)
	{
		str = (char *)lst->content;
		str = ft_expand_word(str);
		if (!str)
			return (-1);
		lst->content = str;
		lst = lst->next;
	}
	return (0);
}

int	ft_files_expand(t_list *lst)
{
	t_redir	*redir;

	redir = NULL;
	while (lst)
	{
		redir = (t_redir *)lst->content;
		if (redir->mode != -1)
		{
			redir->file = ft_expand_word(redir->file);
			if (!redir->file)
				return (-1);
		}
		lst = lst->next;
	}
	return (0);
}

int	ft_expand(t_cmd *cmd_lst)
{
	while (cmd_lst)
	{
		if (ft_args_expand(cmd_lst->w_lst) == -1)
			return (-1);
		if (ft_files_expand(cmd_lst->in_redir) == -1)
			return (-1);
		if (ft_files_expand(cmd_lst->out_redir) == -1)
			return (-1);
		cmd_lst = cmd_lst->next;
	}
	return (0);
}
