
#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "../gnl/get_next_line.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_data
{
    char    **env;
	char	*prompt;
    char    **array_input;
	char	exit_status;
}			t_data;

typedef struct s_redir
{
	char			*file;
	int				mode;
}			t_redir;

typedef struct s_cmd
{
	t_list			*w_lst;
	t_list			*in_redir;
	t_list			*out_redir;
	struct	s_cmd	*next;
}			t_cmd;


// SIGNALS
void		signals(void);
void		handle_ctrl_c(int signal);

// PARSING
int		ft_parse(t_data data, t_cmd *cmd_lst);

// EXPANSION
int		ft_expand(t_cmd *cmd_lst, char **env);
char	*ft_expand_word(char *str, char **env);

// QUOTE REMOVAL
int	remove_quotes(t_cmd *cmd_lst);

// UTILS
void		print_array(char **array);
void		free_array(char **array);
char		*my_getenv(char *str, char **env);
void		ft_file_clear(t_list *files_lst);
int			double_free(char **ptr);
int			free_data(t_data *data, t_cmd *cmd_lst, char mode);


// EXECUTION
void	ft_execute(t_cmd *cmd_lst, char **env);

// BUILTINS
void	main_builtin(t_cmd *cmd_lst, t_data *data);
void	ft_export(char *var, char *value, char **env);

// PATH
char		*get_path_line(char **env);
char		*get_path(char *command, char **env);

#endif