/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 19:28:49 by szapata-          #+#    #+#             */
/*   Updated: 2024/01/02 22:20:59 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>
#include <fcntl.h>

int	check_buffer(char **buffer, char **line, size_t *len)
{
	size_t	len_tmp;
	size_t	buff_len;

	buff_len = ft_strlen(*buffer);
	if (!*len)
		*len = 0;
	if (*len == buff_len)
		return (1);
	len_tmp = *len;
	while (buffer[0][*len])
		if (buffer[0][(*len)++] == '\n')
			break ;
	*line = ft_strjoin(*line, &buffer[0][len_tmp], (*len) - len_tmp);
	if ((*len == buff_len && *len < BUFFER_SIZE) || !*line)
	{
		free(*buffer);
		*len = 0;
		*buffer = 0;
		return (0);
	}
	if (line[0][ft_strlen(*line) - 1] == '\n')
		return (0);
	return (1);
}

int	init_buffer(t_list *head, t_list **list, int fd)
{
	char	*buffer;
	int		i;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
	{
		*list = head;
		return (0);
	}
	i = 0;
	while (i <= BUFFER_SIZE)
		buffer[i++] = 0;
	if (read(fd, buffer, BUFFER_SIZE) < 1)
	{
		if ((*list)->next)
			(*list)->next->prev = (*list)->prev;
		if ((*list)->prev)
			(*list)->prev->next = (*list)->next;
		free(buffer);
		set_list(list, NULL, fd, head);
		return (0);
	}
	(*list)->buffer = buffer;
	return (1);
}

void	set_list(t_list **list, char **line, int fd, t_list *head)
{
	t_list	*tmp;

	if (head)
	{
		tmp = *list;
		if (!(*list)->prev)
			*list = (*list)->next;
		else
			*list = head;
		free(tmp);
		return ;
	}
	*line = 0;
	while ((*list)->fd != fd)
	{
		if ((*list)->next)
			*list = (*list)->next;
		else
			(*list)->next = ft_lstnew(*list, fd);
	}
}

char	*get_next_line(int fd)
{
	static t_list		*list;
	t_list				*head;
	char				*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (!list)
		list = ft_lstnew(NULL, fd);
	head = list;
	line = 0;
	set_list(&list, &line, fd, NULL);
	if (!(list->buffer))
		if (init_buffer(head, &list, fd) < 1)
			return (NULL);
	while (check_buffer(&(list->buffer), &line, &(list->len)))
		if (check_read(read(fd, list->buffer, BUFFER_SIZE)
				, &list, &line, &(list->len)))
			break ;
	while (list && list->prev)
		list = list->prev;
	return (line);
}
