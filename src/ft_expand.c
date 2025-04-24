/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 22:03:04 by szapata-          #+#    #+#             */
/*   Updated: 2025/04/23 18:57:46 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*set_new_word(char *s1, char *tmp, char *s2, char *exp)
{
	char	*var;
	char	*s1_tmp;

	var = tmp;
	s1_tmp = s1;
	while (*s1 != '$')
		*tmp++ = *s1++;
	while (exp && *exp)
		*tmp++ = *exp++;
	while (*s2)
		*tmp++ = *s2++;
	*tmp = '\0';
	free (s1_tmp);
	return (var);
}

char	*ft_expand_var(char *s1, char *s2, char **env)
{
	char	*var;
	char	*exp;
	char	*tmp;
	int		var_len;
	int		sum;

	var = ++s2;
	var_len = 0;
	while (s2 && ft_isalpha(*s2))
		s2++;
	tmp = ft_substr(var, 0, s2 - var);
	if (!tmp)
		return (NULL);
	exp = my_getenv(tmp, env);
	free(tmp);
	if (exp)
		var_len = ft_strlen(exp);
	tmp = ft_strchr(s1, '$');
	sum = tmp - s1 + var_len + ft_strlen(s2) + 1;
	tmp = (char *)malloc(sizeof(char) + sum);
	if (!tmp && my_free(s1))
		return (NULL);
	return (set_new_word(s1, tmp, s2, exp));
}

char	*ft_expand_exit(char *s1, char *s2, t_data *data)
{
	char	*stat;
	char	*tmp;
	int		sum;

	stat = ft_itoa(data->exit_status);
	if (!stat && my_free(s1))
		return (NULL);
	s2 += 2;
	tmp = ft_strchr(s1, '$');
	sum = tmp - s1 + ft_strlen(stat) + ft_strlen(s2) + 1;
	tmp = (char *)malloc(sizeof(char) + sum);
	if (!tmp && my_free(s1))
		return (NULL);
	return (set_new_word(s1, tmp, s2, stat));
}

char	*ft_expand_loop(char *str, char *tmp, t_data *data)
{
	char	q;

	q = 0;
	while (tmp && str && *str)
	{
		if (*str == '\"')
			++q;
		if (*str == '\'' && !(q % 2) && str++)
			while (*str && *str != '\'')
				str++;
		if (*str == '$')
		{
			if (*(str + 1) == '?')
				tmp = ft_expand_exit(tmp, str, data);
			else
				tmp = ft_expand_var(tmp, str, data->env);
			if (!tmp)
				return (NULL);
		}
		str++;
	}
	return (tmp);
}

char	*ft_expand_word(char *str, t_data *data)
{
	char	*tmp;
	char	*tmp2;
	char	*res;

	tmp = ft_strdup(str);
	tmp2 = str;
	res = ft_expand_loop(str, tmp, data);
	free(tmp2);
	return (res);
}
