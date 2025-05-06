/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 19:30:32 by szapata-          #+#    #+#             */
/*   Updated: 2024/01/02 22:20:45 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
# include <unistd.h>
# include <stdlib.h>

typedef struct s_list
{
	int				fd;
	size_t			len;
	char			*buffer;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;
char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2, size_t len);
size_t	ft_strlen(char *str);
void	set_new_line(char **line, char *buffer, size_t len);
int		check_read(int r_status, t_list **list, char **line, size_t *len);
int		init_buffer(t_list *head, t_list **list, int fd);
void	set_list(t_list **list, char **line, int fd, t_list *head);
t_list	*ft_lstnew(t_list *prev, int fd);
int		check_buffer(char **buffer, char **line, size_t *len);

#endif