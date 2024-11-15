#include "../include/minishell.h"

int	ft_free(void *ptr)
{
	free(ptr);
	return (1);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (s2);
	else if (!s2)
		return (s1);
	return (ft_strjoin(s1, s2));
}

// int	ft_expand(char **res, char *prompt)
// {
// 	char	*tmp;
// 	int		count;
// 	char	*var;
// 	char	*var2;

// 	tmp = *res;
// 	prompt++;
// 	count = 0;
// 	while (ft_isalnum(*prompt++))
// 		count++;
// 	if (!count)
// 		return (1);
// 	var = ft_substr(prompt - count, 0, count);
// 	var2 = getenv(var);
// }

char	set_flags(char **c)
{
	char	s;

	s = **c;
	(*c)++;
	if (s == '<' && **c == '<' && (*c)++)
		return (1);
	else if (s == '>' && **c == '>' && (*c)++)
		return (2);
	else if (s == '<')
		return (4);
	else
		return (8);
}

int	ft_ismeta(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int	ft_isdelimiter(char c)
{
	if (c == '>' || c == '<' || c == '|' || c == ' ' || c == '\0')
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
	if (!node && ft_free(redir))
		return (-1);
	if (flags & 4 || flags & 1)
	{
		redir->mode = O_RDONLY | O_CREAT;
		if (flags & 1)
			redir->mode = -1;
		ft_lstadd_back(&(cmd_lst->in_redir), node);
	}
	else
	{
		redir->mode = O_RDWR | O_CREAT | O_TRUNC;
		if (flags & 2)
			redir->mode = O_WRONLY | O_CREAT | O_APPEND;
		ft_lstadd_back(&(cmd_lst->out_redir), node);
	}
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
	char	q;

	while (**prompt == ' ')
		(*prompt)++;
	start = *prompt;
	q = 0;
	while (!ft_isdelimiter(**prompt))
	{
		if (**prompt == '\'' || **prompt == '\"')
		{
			q = **prompt;
			(*prompt)++;
			(*prompt) = ft_strchr((*prompt), q);
			if (!(*prompt))
				return (-1);
		}
		(*prompt)++;
	}
	if (start == *prompt)
		return (-1);
	if (add_word_to_list(start, *prompt, flags, cmd_lst) == -1)
		return (-1);
	while (*prompt && **prompt == ' ')
		(*prompt)++;
	return (0);
}

int	ft_print_err(char *prompt)
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
	return (1);
}

int	ft_parse(t_data data, t_cmd *cmd_lst)
{
	char	*prompt;
	char	flags;

	prompt = data.prompt;
	while (*prompt != '\0')
	{
		flags = 0;
		while(*prompt == ' ')
			prompt++;
		if (ft_ismeta(*prompt))
			flags = set_flags(&prompt);
		if (add_word(&prompt, flags, cmd_lst) == -1
			&& ft_print_err(prompt))
			return (-1);
		if (*prompt == '|' && prompt++)
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