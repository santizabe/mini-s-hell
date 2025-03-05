/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 22:03:04 by szapata-          #+#    #+#             */
/*   Updated: 2025/03/02 16:56:38 by szapata-         ###   ########.fr       */
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
	if (!tmp)
		return (NULL);
	return (set_new_word(s1, tmp, s2, exp));
}

char	*ft_expand_word(char *str, char **env)
{
	char	*tmp;
	char	q;

	tmp = str;
	q = 0;
	while (str && *str)
	{
		if (*str == '\"')
			++q;
		if (*str == '\'' && !(q % 2) && str++)
			while (*str && *str != '\'')
				str++;
		if (*str == '$')
		{
			tmp = ft_expand_var(tmp, str, env);
			if (!tmp)
				return (NULL);
		}
		str++;
	}
	return (tmp);
}
