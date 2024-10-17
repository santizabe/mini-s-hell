#include "../include/minishell.h"

void execution (t_data *data)
{
    //Esto ejecuta un comando
    char *path = get_path(data->array_input[0], data->env);
    printf("Path: %s\n", path);
    execve(path, data->array_input, data->env);
    //Solo funciona si solo le pasamos un comando. Si le pasamos un comando con argumentos no funciona.
}