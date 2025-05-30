/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:26:19 by szapata-          #+#    #+#             */
/*   Updated: 2025/05/06 18:25:22 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	redir_handler(char *str, int flags, t_cmd *cmd_lst)
{
	t_redir	*redir;
	t_list	*node;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (-1);
	redir->file = str;
	node = ft_lstnew(redir);
	if (!node && ft_free(redir))
		return (-1);
	if ((flags & 4 || flags & 1) && set_redir_mode(redir, flags))
		ft_lstadd_back(&(cmd_lst->in_redir), node);
	else
	{
		set_redir_mode(redir, flags);
		ft_lstadd_back(&(cmd_lst->out_redir), node);
	}
	if (redir->mode != -1)
		ft_lstadd_back(&(cmd_lst->lst_order), ft_lstnew(node->content));
	return (0);
}

int	add_word_to_list(char *start, char *end, int flags, t_cmd *cmd_lst)
{
	char	*str;
	t_list	*node;

	str = ft_substr(start, 0, end - start);
	if (!str)
		return (-1);
	if (flags)
		return (redir_handler(str, flags, cmd_lst));
	node = ft_lstnew(str);
	if (!node && ft_free(str))
		return (-1);
	else
		ft_lstadd_back(&(cmd_lst->w_lst), node);
	return (0);
}

int	add_word(char **prompt, int flags, t_cmd *cmd_lst)
{
	char	*start;

	while (**prompt == ' ')
		(*prompt)++;
	start = *prompt;
	*prompt = iter_prompt(prompt);
	if (!(*prompt) || start == *prompt)
		return (-1);
	if (add_word_to_list(start, *prompt, flags, cmd_lst) == -1)
		return (-1);
	while (*prompt && **prompt == ' ')
		(*prompt)++;
	return (0);
}

static int	ft_print_err(char *prompt, t_data *data)
{
	char	*err_msg;

	err_msg = "syntax error near unexpected token `";
	ft_putstr_fd(err_msg, 2);
	if (!prompt || !*prompt)
		ft_putstr_fd("newline'", 2);
	else
	{
		write(2, &prompt[0], 1);
		write(2, "'", 1);
	}
	ft_putstr_fd("\n", 2);
	data->exit_status = 2;
	return (1);
}

/**
 * @brief Parses shell input into a command list structure.
 * 
 * @param data Container holding the input prompt to parse.
 * @param cmd_lst Pointer to the command list where parsed elements will 
 * be stored.
 * @return 0 on success, -1 on memory allocation failure or parsing error.
 * @note Handles spaces, meta-characters, pipes, and builds a linked list 
 * of commands.
 * @warning The command list must be properly initialized before calling 
 * this function.
 *          Caller is responsible for freeing the allocated command list memory.
 */
int	ft_parse(t_data data, t_cmd *cmd_lst)
{
	char	*prompt;
	char	flags;

	prompt = data.prompt;
	while (*prompt != '\0')
	{
		flags = 0;
		while (*prompt == ' ')
			prompt++;
		if (ft_ismeta(*prompt))
			flags = set_flags(&prompt);
		if (add_word(&prompt, flags, cmd_lst) == -1
			&& ft_print_err(prompt, &data))
			return (-1);
		if (*prompt == '|' && *(prompt + 1) && prompt++)
		{
			cmd_lst->next = (t_cmd *)malloc(sizeof(t_cmd));
			if (!cmd_lst->next)
				return (-1);
			cmd_lst = cmd_lst->next;
			ft_memset(cmd_lst, 0, sizeof(t_cmd));
		}
	}
	return (0);
}
