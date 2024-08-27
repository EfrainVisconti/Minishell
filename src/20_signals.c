/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   19_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 20:55:08 by eviscont          #+#    #+#             */
/*   Updated: 2024/08/25 20:55:22 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	handler_true(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	return ;
}

static void	handler_false(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		write(STDOUT_FILENO, "Quit (core dump)\n", 17);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	init_signals(int *signal_comand)
{
	if (*signal_comand)
	{
		signal(SIGINT, &handler_true);
		signal(SIGQUIT, &handler_false);
	}
	else if (!*signal_comand)
	{
		signal(SIGINT, &handler_false);
		signal(SIGQUIT, SIG_IGN);
		*signal_comand = FALSE;
	}
}
