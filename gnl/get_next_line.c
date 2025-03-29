/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 19:28:49 by szapata-          #+#    #+#             */
/*   Updated: 2025/03/07 10:52:49 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	check_buffer(char **buffer, char **line, size_t *len)
{
	size_t	len_tmp;
	size_t	buff_len;

	buff_len = gnl_ft_strlen(*buffer);
	if (!*len)
		*len = 0;
	if (*len == buff_len)
		return (1);
	len_tmp = *len;
	while (buffer[0][*len])
		if (buffer[0][(*len)++] == '\n')
			break ;
	set_new_line(line, &buffer[0][len_tmp], (*len) - len_tmp);
	if ((*len == buff_len && *len < BUFFER_SIZE) || !*line)
	{
		free(*buffer);
		*len = 0;
		*buffer = 0;
		return (0);
	}
	if (line[0][gnl_ft_strlen(*line) - 1] == '\n')
		return (0);
	return (1);
}

int	init_buffer(char **buffer, int fd)
{
	unsigned int	i;

	*buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!*buffer)
		return (0);
	i = 0;
	while (i <= BUFFER_SIZE)
		buffer[0][i++] = 0;
	if (read(fd, *buffer, BUFFER_SIZE) < 1)
	{
		free(*buffer);
		*buffer = 0;
		return (0);
	}
	return (1);
}

void	set_new_line(char **line, char *buffer, size_t len)
{
	char	*new_line;
	char	*tmp;

	new_line = (char *)malloc(len + 1);
	if (!new_line)
	{
		if (*line)
			free(*line);
		return ;
	}
	new_line[len] = 0;
	tmp = new_line;
	while (len--)
		new_line[len] = buffer[len];
	*line = gnl_ft_strjoin(*line, tmp);
	free(tmp);
}

char	*get_next_line(int fd)
{
	static char		*buffer;
	char			*line;
	static size_t	len;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (!buffer)
		if (init_buffer(&buffer, fd) < 1)
			return (NULL);
	line = 0;
	while (check_buffer(&buffer, &line, &len))
		if (check_read(read(fd, buffer, BUFFER_SIZE), &buffer, &line, &len))
			break ;
	return (line);
}

// int	main(void)
// {
// 	char	*line;
// 	int		fd;

// 	fd = open("hello.txt", O_RDONLY);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);
// 	close(fd);
// 	return (0);
// }
