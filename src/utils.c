#include "../include/minishell.h"

void print_array(char **array)
{
    int i = 0;
    while (array[i])
    {
        printf("[%d]: %s\n", i, array[i]);
        i++;
    }
}
void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}