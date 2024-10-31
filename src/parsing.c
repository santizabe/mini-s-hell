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

int	set_flags(char *c, char	*flags)
{
	int	ret_stat;

	ret_stat = 1;
	if (*c == '\"' && !(*flags & 1))
		*flags += *flags & 1;
	else if (*c == '\'' && !(*flags & 2))
		*flags += *flags & 2;
	else if (*c == '<' || *c == '>'
		&& (*flags & 4 || *flags & 8 || *flags & 16 || *flags & 32))
		*flags = -1;
	else if (*c == '<' && *(c + 1) == '<' && !(*flags & 16)
		&& ret_stat++)
		*flags += *flags & 16;
	else if (*c == '>' && *(c + 1) == '>' && !(*flags & 32)
		&& ret_stat++)
		*flags += *flags & 32;
	else if (*c == '<' && !(*flags & 4))
		*flags += *flags & 4;
	else if (*c == '>' && !(*flags & 8))
		*flags += *flags & 8;
	return (ret_stat);
}

int	ft_ismeta(char c)
{
	if (c == '<' || c == '>' || c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	ft_parse(t_data data, t_cmd *cmd_lst)
{
	int		i;
	char	*prompt;
	char	flags;

	i = 0;
	flags = 0;
	prompt = data.prompt;
	while (prompt[i] != '\n')
	{
		while(prompt[i] == ' ' && (!(flags & 1) && !(flags & 2)))
			i++;
		if (ft_ismeta(prompt[i]))
			i += set_flags(&prompt[i], &flags);
		if (prompt[i] == '$')
			i += ft_expand(&prompt[i], flags);
		i += token_manager(&prompt[i], flags);
	}
}