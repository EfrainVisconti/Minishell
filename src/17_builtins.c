/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   17_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 19:35:10 by eviscont          #+#    #+#             */
/*   Updated: 2024/08/27 19:39:21 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_echo_aux(t_node *node, int fd, int i, int len)
{
	while (node->full_cmd[i])
	{
		if (!ft_strcmp(node->full_cmd[i], "-n"))
		{
			i++;
		}
		else
		{
			ft_putstr_fd(node->full_cmd[i], fd);
			if (i++ < len - 1)
				ft_putstr_fd(" ", fd);
		}
	}
}

void	ft_echo(t_node *node, int fd)
{
	int	i;
	int	len;

	len = ft_arraylen(node->full_cmd);
	i = 1;
	if (len > 1 && !ft_strcmp(node->full_cmd[i], "-n"))
	{
		i++;
		ft_echo_aux(node, fd, i, len);
	}
	else
	{
		while (node->full_cmd[i])
		{
			ft_putstr_fd(node->full_cmd[i], fd);
			if (i++ < len - 1)
				ft_putstr_fd(" ", fd);
		}
		ft_putstr_fd("\n", fd);
	}
}
