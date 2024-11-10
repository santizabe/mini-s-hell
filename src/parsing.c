#include "../include/minishell.h"

char	*ft_strjoin2(char *s1, char *s2, int len)
{
	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (s2);
	else if (!s2)
		return (s1);
	return (ft_strjoin(s1, s2));
}

int	ft_expand(char **res, char *prompt)
{
	char	*tmp;
	int		count;
	char	*var;
	char	*var2;

	tmp = *res;
	prompt++;
	count = 0;
	while (ft_isalnum(*prompt++))
		count++;
	if (!count)
		return (1);
	var = ft_substr(prompt - count, 0, count);
	var2 = getenv(var);
}

void	set_flags(char **c, char *flags)
{
	char	s;

	s = **c;
	(*c)++;
	if (s == '<' && **c == '<' && (*c)++)
		*flags = *flags & 1;
	else if (s == '>' && **c == '>' && (*c)++)
		*flags = *flags & 2;
	else if (s == '<')
		*flags = *flags & 4;
	else
		*flags = *flags & 8;
}

int	ft_ismeta(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int	ft_isdelimiter(char c)
{
	if (c == '>' || c == '<' || c == '|' || c == ' ' || c == '\n')
		return (1);
	return (0);
}

int	redir_handler(char *str, int flags, t_cmd *cmd_lst)
{
	t_redir	*redir;
	t_list	*node;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (-1);
	redir->file = str;
	node = ft_lstnew(redir);
	if (!node)
		return (-1);
	if (flags & 1)
		ft_lstadd_front(&(cmd_lst->limiter), node);
	else if (flags & 2)
	{
		redir->mode = O_WRONLY | O_CREAT | O_APPEND;
		ft_lstadd_front(&(cmd_lst->out_redir), node);
	}
	else if (flags & 4)
	{
		redir->mode = O_RDONLY | O_CREAT;
		ft_lstadd_front(&(cmd_lst->in_redir), node);
	}
	else
	{
		redir->mode = O_RDWR | O_CREAT | O_TRUNC;
		ft_lstadd_front(&(cmd_lst->out_redir), node);
	}
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
	if (!node)
		return (-1);
	ft_lstadd_front(&(cmd_lst->w_lst), node);
	return (0);
}

int	add_word(char **prompt, int flags, t_cmd *cmd_lst)
{
	char	*start;
	int		count;

	while (**prompt == ' ')
		(*prompt)++;
	start = *prompt;
	while (!ft_isdelimiter(**prompt))
	{
		if (**prompt == '\'' || **prompt == '\"')
		{
			*prompt = ft_strchr((*prompt + 1), *(*prompt++));
			if (!(*prompt))
				return (-1);
		}
		(*prompt)++;
	}
	if (add_word_to_list(start, *prompt, flags, cmd_lst) == -1)
		return (-1);
	return (0);
}

int	ft_parse(t_data data, t_cmd *cmd_lst)
{
	int		i;
	char	*prompt;
	char	flags;

	i = 0;
	prompt = data.prompt;
	while (*prompt != '\n')
	{
		flags = 0;
		while(*prompt == ' ')
			prompt++;
		if (ft_ismeta(*prompt))
			set_flags(&prompt, &flags);
		if (add_word(&prompt, flags, cmd_lst) == -1)
			return (-1);
	}
	return (0);
}