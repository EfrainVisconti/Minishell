/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   18_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:58:31 by eviscont          #+#    #+#             */
/*   Updated: 2024/08/27 14:45:58 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_error3(int id, char *s)
{
	if (id == 17)
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
	else if (id == 18)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (id == 19)
		ft_putstr_fd("cd: too many arguments\n", 2);
	else if (id == 20)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (id == 21)
		ft_putstr_fd("export: not a valid identifier\n", 2);
}

void	print_error2(int id, char *s)
{
	if (id == 11)
	{
		g_status = 1;
		ft_putstr_fd(s, 2);
		ft_putstr_fd(" : No such file or directory\n", 2);
	}
	else if (id == 12)
	{
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else if (id == 13)
		ft_putstr_fd("Error with input file or pipe output\n", 2);
	else if (id == 14)
		ft_putstr_fd("Error with output file\n", 2);
	else if (id == 16)
		ft_putstr_fd("exit\nexit: too many arguments\n", 2);
	else
		print_error3(id, s);
}

void	print_error(int id, char *s)
{
	g_status = 2;
	if (id == 1)
		ft_putstr_fd("error: open quotes\n", 2);
	else if (id == 2)
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
	else if (id == 3)
		ft_putstr_fd("syntax error near unexpected token `>'\n", 2);
	else if (id == 4)
		ft_putstr_fd("syntax error near unexpected token `<'\n", 2);
	else if (id == 5)
		ft_putstr_fd("syntax error near unexpected token `>>'\n", 2);
	else if (id == 6)
		ft_putstr_fd("syntax error near unexpected token `<<'\n", 2);
	else if (id == 8)
		ft_putstr_fd("syntax error near unexpected token `REDIR'\n", 2);
	else if (id == 9)
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
	else if (id == 10)
	{
		g_status = 1;
		ft_putstr_fd(" : No such file or directory\n", 2);
	}
	else
		print_error2(id, s);
}
