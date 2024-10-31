#include "../include/minishell.h"

int	only_spaces(char *input)
{
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

void	history(char *input)
{
	if (input != NULL && ft_strlen(input) != 0 && only_spaces(input) == 0)
	{
		add_history(input);
	}
}

void	init_data(t_data *data, char **env, t_cmd **cmd_lst)
{
	data->env = env;
	//print_array(data->env);
	data->prompt = NULL;
	data->array_input = NULL;
	*cmd_lst = ft_lstnew(0);
	ft_memset(*cmd_lst, 0, sizeof(t_cmd));
}

void    free_data(t_data *data, t_cmd *cmd_lst)
{
	ft_lstclear(&(cmd_lst->w_lst), free);
	ft_lstclear(&(cmd_lst->in_redir), free);
	ft_lstclear(&(cmd_lst->out_redir), free);
	rl_clear_history();
    free(data->prompt);
}

int	main(int argc, char** argv, char **env)
{
	t_data	data;
	t_cmd	*cmd_lst;

	signals();
	while (1)
	{
		init_data(&data, env, &cmd_lst);
		data.prompt = readline("MiniShell> ");
		if (data.prompt)
		{
			history(data.prompt);
			ft_parse(data, cmd_lst);
			//ft_execute(data, cmd_lst);
		}
    	free_data(&data, cmd_lst);
	}
	return (0);
}
