/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 12:54:01 by szapata-          #+#    #+#             */
/*   Updated: 2024/01/02 15:20:46 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_list	*ft_lstnew(t_list *prev, int fd)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->fd = fd;
	new_node->len = 0;
	new_node->buffer = NULL;
	new_node->next = NULL;
	new_node->prev = prev;
	return (new_node);
}

char	*ft_strjoin(char *s1, char *s2, size_t len)
{
	char	*s;
	char	*tmp;
	int		s1_len;
	int		i;

	s1_len = ft_strlen(s1);
	s = (char *)malloc(s1_len + len + 1);
	if (!s)
		return (s);
	tmp = s;
	i = 0;
	while (s1_len--)
		*s++ = s1[i++];
	while (len--)
		*s++ = *s2++;
	*s = 0;
	if (s1)
		free(s1);
	return (tmp);
}

size_t	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (*str)
	{
		i++;
		str++;
	}
	return (i);
}

int	check_read(int r_status, t_list **list, char **line, size_t *len)
{
	t_list	*head;

	head = *list;
	while (head->prev)
		head = head->prev;
	if (r_status < 1)
	{
		if ((*list)->next)
			(*list)->next->prev = (*list)->prev;
		if ((*list)->prev)
			(*list)->prev->next = (*list)->next;
		free((*list)->buffer);
		set_list(list, NULL, (*list)->fd, head);
		if (r_status < 0)
			if (*line)
				free(*line);
		return (1);
	}
	if (*len == ft_strlen(((*list)->buffer)))
		*len = 0;
	if (r_status < BUFFER_SIZE)
		((*list)->buffer)[r_status] = '\0';
	return (0);
}
