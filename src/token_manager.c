/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:47:21 by szapata-          #+#    #+#             */
/*   Updated: 2024/11/11 14:34:45 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../include/minishell.h"

// int	d_quote_manager(char *prompt, char flags, t_cmd *cmd_lst)
// {
// 	char	*c_quote;

// 	c_quote = ft_strchr(prompt, '\"');
// 	if (!c_quote)
// 		return (-1);
// }

// int	set_here_doc(char *prompt, char flags, t_cmd *cmd_lst)
// {
// 	int	count;
// 	int	blank;
	
// 	count = 0;
// 	blank = 0;
// 	// skip blanks, count the characters, apply quote removal if
// 	// needed and add it to the here_doc list.
// 	while (prompt[blank] == ' ')
// 		blank++;
	
// 	return (count + blank);
// }

// int	token_manager(char *prompt, char flags, t_cmd *cmd_lst)
// {
// 	int	count;

// 	count = 0;
// 	if (flags & 1)
// 		count += d_quote_manager(prompt, flags, cmd_lst);
// 	else if (flags & 2)
// 		count += s_quote_manager(prompt, flags, cmd_lst);
// 	else if (flags & 4 | flags & 8 | flags & 32)
// 		count += redir_manager(prompt, flags, cmd_lst);
// 	else if (flags & 16)
// 		count += set_here_doc(prompt, flags, cmd_lst);
// 	else
// 		count += add_word(prompt, flags, cmd_lst);
// 	return (count);
// }