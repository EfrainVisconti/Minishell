/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   14_execute_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:45:08 by eviscont          #+#    #+#             */
/*   Updated: 2024/08/14 18:47:43 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	execute_commands(t_minishell *mini)
{
	pid_t	pid;

	pid = 0;
	if (mini->nbr_nodes == 1)
	{
		if (is_builtin(mini->nodes[0]->full_cmd[0])
		&& mini->nodes[0]->is_exec)
			ft_printf("Exec one Bultin command\n");
		else if (!is_builtin(mini->nodes[0]->full_cmd[0])
		&& mini->nodes[0]->is_exec)
		{
			pid = fork();
			if (pid == -1)
				return ;
			else if (pid == 0)
			{
				if (execve(mini->nodes[0]->full_path, mini->nodes[0]->full_cmd, mini->argenv) == -1)
					exit (1);
			}
			else
				waitpid(pid, &g_status, 0);
		}
	}
	else
		ft_printf("TO DO WITH PIPES\n");
}
