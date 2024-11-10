#include "../include/minishell.h"

void	history(char *input)
{
	if (input != NULL && ft_strlen(input) != 0 && only_spaces(input) == 0)
	{
		add_history(input);
	}
}

int	d_ptrlen(char **ptr)
{
	int	count;

	count = 0;
	while (ptr && *ptr && ++count)
		ptr++;
	return (count);
}

int	double_free(char **ptr)
{
	char	**tmp;

	tmp = ptr;
	while (ptr && *ptr)
		free(*ptr++);
	free(tmp);
	return (1);
}

int	copy_env(char **dst, char **src)
{
	int	env_len;
	int	i;

	env_len = d_ptrlen(src);
	dst = (char **)malloc((env_len + 1) * sizeof(char *));
	if (!dst)
		return (-1);
	dst[env_len] = NULL;
	i = 0;
	while (i < env_len)
	{
		dst[i] = ft_strdup(src[i]);
		if (!dst[i] && double_free(dst))
			return (NULL);
	}
	return (0);
}

int	init_data(t_data *data, char **env, t_cmd **cmd_lst)
{
	if (copy_env(&(data->env), env) == -1)
		return (-1);
	data->prompt = NULL;
	(*cmd_lst) = ft_lstnew(0);
	ft_memset(*cmd_lst, 0, sizeof(t_cmd));
}

void    free_data(t_data *data, t_cmd *cmd_lst)
{
	ft_lstclear(&(cmd_lst->w_lst), free);
	ft_lstclear(&(cmd_lst->in_redir), free);
	ft_lstclear(&(cmd_lst->out_redir), free);
	rl_clear_history();
    free(data->prompt);
	double_free(data->env);
}

int	main(int argc, char** argv, char **env)
{
	t_data	data;
	t_cmd	*cmd_lst;

	signals();
	while (1)
	{
		if (init_data(&data, env, &cmd_lst) == -1)
			break ;
		data.prompt = readline("MiniShell> ");
		if (data.prompt)
		{
			history(data.prompt);
			if (ft_parse(data, cmd_lst) == -1)
				print_error();
			else
				ft_execute(data, cmd_lst);
		}
    	free_data(&data, cmd_lst);
	}
	return (0);
}
