/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:22:03 by szapata-          #+#    #+#             */
/*   Updated: 2025/03/11 14:36:48 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_ctrl_c(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void signals(void)
{
	signal(SIGINT, handle_ctrl_c); // Ctrl+C imprime una nueva entrada en una línea nueva.
	signal(SIGQUIT, SIG_IGN); // Ctrl+\ debe ignorarse.
 	signal(SIGTSTP, SIG_IGN); // Ctrl+Z debe ignorarse.
    //Ctrl+D debe cerrar el programa. Pero esto no lo hacemos con las señales porque cuando pulsamos ctrl+d es como si por readline le metieramos Null y entonces el bucle principal del main se cierra.
}
